#include "Tuple_gen.h"
#include <QRandomGenerator>
#include <cstdlib>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QTextStream>
#include <QElapsedTimer>
#include <QDate>
#include <QFile>
#include <QDataStream>
#include <vector>
#include <QVector>
#include <QPair>
#include <algorithm>
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlError>

using namespace std;
QString gen_date_series(QElapsedTimer &time)
{
    static QDate curr(2020,11,25);
    QRandomGenerator gen_date(static_cast<int>(time.nsecsElapsed()));
    QString date;
    date=(curr.addDays(gen_date.generate()%3).toString(Qt::ISODate));
    curr.operator=(curr.fromString(date,Qt::ISODate));
    date.push_front("'");
    date.push_back("'");
    return date;
}
QString gen_char(QElapsedTimer &time)
{
    QRandomGenerator gen_ch(static_cast<int>(time.nsecsElapsed()));
    QString ch;
    ch.push_back(static_cast<char>(gen_ch.generate64()%25+97));
    return ch;
}
QString gen_str(QElapsedTimer &time)
{
    QString str;
    QRandomGenerator gen_len(static_cast<int>(time.nsecsElapsed()));
    int length=gen_len.generate()%10+2;
    str.push_back(gen_char(time).toUpper());
    for (int i=0;i<length-1;++i)
    {
        str.push_back(gen_char(time));
    }
    return str;
}
int gen_num(QElapsedTimer &time,int from,int to)
{
    srand(static_cast<int>(time.nsecsElapsed()));
    return rand()%(to-from)+from;
}

QVector<QString> gen_artists(int amount,QVector<QString> &artNames)
{
    QElapsedTimer t;
    t.start();
    QVector<int> idx_names;
    int artCount=artNames.size(); 
    for (int i=0;i<amount;++i)
    {
        int idx=gen_num(t,0,artCount-1);
        QVector<int>::iterator it=idx_names.begin();
        while (it!=idx_names.end())
        {
            if (idx==*it)
            {
                it=idx_names.begin();
                idx=gen_num(t,0,artCount-1);
            }
            else
            {
                ++it;
            }
        }
        idx_names.push_back(idx);
     }
    QVector<QString> names;
    for (int i=0;i<amount;++i)
    {
        names.push_back(artNames[idx_names[i]]);
    }
    return names;
}

bool gen_tuple_id_artists(int amount,QSqlQuery *q)
{
    if (amount>0)
    {
        QTextStream out(stdout);
        QString cmd;
        QElapsedTimer t;
        t.start();
        QFile poster_data("C:/Users/Hp/Desktop/QT projects/DB2/last_tuples.bin");
        QFile artists_data("C:/Users/Hp/Desktop/QT projects/DB2/artists.bin");
        int idx,limit;
        QPair<int,int> min_max;
        QVector<QString> artNames;
        if (poster_data.open(QIODevice::ReadWrite)&&artists_data.open(QIODevice::ReadOnly))
        {
            QDataStream io_p(&poster_data), io_a(&artists_data);
            io_p>>min_max;
            io_a>>artNames;
            poster_data.close();
            artists_data.close();
            idx=min_max.first;
            limit=min_max.second;
        }
        for (int i=0;i<amount;++i)
        {
            int length=gen_num(t,1,artNames.size());
            QVector<QString> names=gen_artists(length,artNames);
            for (int i=0;i<length;++i)
            {
                cmd="INSERT INTO id_artists VALUES("+QString().setNum(idx)+",'"+names[i]+"');";
                qDebug()<<cmd<<Qt::endl;
                if (!q->exec(cmd))
                {
                    QMessageBox *errBox=new QMessageBox(QMessageBox::Critical,"Error",q->lastError().text());
                    errBox->exec();
                    return 0;
                }
                cmd.clear();
            }
            ++idx;
            if (idx>limit)break;
        }
        if (poster_data.open(QIODevice::WriteOnly))
        {
             QDataStream io_p(&poster_data);
             io_p<<min_max<<true;
             poster_data.close();
        }
    }

    return 1;

}

bool gen_tuple_poster(int amount,QSqlQuery *q)
{
    if (amount>0)
    {
        QElapsedTimer t;
        bool wasRed=false;
        t.start();
        QTextStream out(stdout);
        QString cmd;
        QPair<int,int> min_max;
        QFile poster_data("C:/Users/Hp/Desktop/QT projects/DB2/last_tuples.bin");//в файле записаны мин и макс индексы строк пршлой генерации
        int cur_idx;
        if (poster_data.open(QIODevice::ReadWrite))
        {
            QDataStream io_p(&poster_data);
            io_p>>min_max>>wasRed;//прошлый максимальный индекс становится минимальным-1 в текущий раз
            if (!wasRed)
            {
                cur_idx=min_max.second;
               min_max.second+=amount;
                ++min_max.first;
            }
            else
            {
                cur_idx=min_max.second;
                min_max.first=min_max.second+1;//новый минимальный
                min_max.second+=amount;//новый максимальный

            }
            ++cur_idx;

            poster_data.close();
            poster_data.open(QIODevice::WriteOnly);
            QDataStream io(&poster_data);
            io<<min_max;
            poster_data.close();
             for (int i=0;i<amount;++i)
             {
                 cmd="INSERT INTO poster VALUES ("+QString().setNum(cur_idx+i)+","+gen_date_series(t)+",'"+gen_str(t)+"',"+QString().setNum(gen_num(t,900,10000))+");";
                 qDebug()<<cmd<<Qt::endl;
                 if (!q->exec(cmd))
                 {
                     QMessageBox *errBox=new QMessageBox(QMessageBox::Critical,"Error",q->lastError().text());
                     errBox->exec();
                     return 0;
                 }
                 cmd.clear();
             }
        }
    }

    return 1;
}

bool gen_tuple_artists(int amount,QSqlQuery *q)
{
    if (amount>0)
    {
        QTextStream out(stdout);
        QString cmd;
        QElapsedTimer t;
        t.start();
        QVector<QString> artNames;
        QFile artists_bin("C:/Users/Hp/Desktop/QT projects/DB2/artists.bin");
        if (artists_bin.open(QIODevice::ReadWrite))
        {
            QDataStream io(&artists_bin);
            io>>artNames;
            artists_bin.close();
            for (int i=0;i<amount;++i)
            {
                QString art_name=gen_str(t);
                artNames.push_back(art_name);
                cmd.push_back("INSERT INTO artists(name,salary) VALUES('"+art_name+"',"+QString().setNum(gen_num(t,25000,100000))+");");
                qDebug()<<cmd<<Qt::endl;
                if (!q->exec(cmd))
                {
                    QMessageBox *errBox=new QMessageBox(QMessageBox::Critical,"Error",q->lastError().text());
                    errBox->exec();
                    return 0;
                }
                cmd.clear();
            }

            artists_bin.open(QIODevice::WriteOnly);
            QDataStream o(&artists_bin);
            o<<artNames;
            artists_bin.close();
        }
        else
        {
            out<<"shit";
            return 0;
        }
    }
    return 1;
}
//////////////////////////STORE//////////////////////////////////////////
//QString gen_str_arr(QElapsedTimer &time)
//{
//    QElapsedTimer t;
//    t.start();
//    QString arr="{";
//    QRandomGenerator gen_len(static_cast<int>(time.nsecsElapsed()));
//    int length=gen_len.generate()%5+2;
//    for (int i=0;i<length;++i)
//    {
//        arr.push_back("\""+gen_str(t)+"\"");
//        if (i!=length-1)
//        {
//            arr.push_back(",");
//        }
//    }
//    arr.push_back("}");
//    return arr;
//}
//QString gen_str_arr(QString fileName,QElapsedTimer &time,bool repeat)
//{
//    QElapsedTimer t;
//    t.start();
//    QRandomGenerator gen_len(static_cast<int>(time.nsecsElapsed()));
//    int length=gen_len.generate()%5+2;
//    int amount;
//    QString arr="{";
//    QFile file(fileName);
//    QDataStream in(&file);
//    if (file.exists()&&file.open(QIODevice::ReadOnly))
//    {
//        in>>amount;
//        QString *name_arr=new QString[amount];
//        for (int i=0;i<amount;++i)
//        {
//            in>>name_arr[i];
//            name_arr[i].chop(1);
//        }
//        file.close();
//        std::vector<int> idx_arr(length,-1);
//        for (int i=0;i<length;++i)
//        {
//            int idx=gen_num(t,0,amount);
//            if (repeat==false)
//            {
//                std::vector<int>::iterator it=idx_arr.begin();
//                while (it!=idx_arr.end())
//                {
//                    if (idx==*it)
//                    {
//                        idx=gen_num(t,0,amount);
//                        it=idx_arr.begin();
//                    }
//                    else
//                    {
//                        ++it;
//                    }
//                }
//                idx_arr[i]=idx;
//            }
//            arr.push_back("\""+name_arr[idx]+"\"");
//            if (i!=length-1)
//            {
//                arr.push_back(",");
//            }
//        }
//        arr.push_back("}");
//        delete[] name_arr;
//    }
//    else
//    {
//        return "";
//    }
//    return arr;

//}
