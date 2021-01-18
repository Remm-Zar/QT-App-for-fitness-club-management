#include "add_client.h"
#include "ui_add_client.h"
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QDate>
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QDebug>
#include <QVector>
#include <Tuple_gen.h>
#include <QElapsedTimer>

QVector<QString> Add_client::male_images={"ava1.png","ava2.png","ava3.png","ava4.png","ava5.png","ava6.png","ava7.png","ava8.png"};
QVector<QString> Add_client::female_images={"ava1.png","ava2.png","ava3.png","ava4.png","ava5.png","ava6.png","ava7.png","ava8.png","ava9.png"};

Add_client::Add_client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add_client)
{
    ui->setupUi(this);
    ui->graphicsView->setStyleSheet("QGraphicsView {background-image:url(:/new/no_image/Materials/avatar/no_image.png)};");
}

Add_client::~Add_client()
{
    delete m_db;
    delete q;
    delete ui;
}

void Add_client::on_pushButton_clicked()
{
    QPixmap *map=new QPixmap(":/new/images/Materials/Icons 32x32/stop.png");
    QIcon ico_bad(":/new/images/Materials/Icons 32x32/stop.ico");
    QMessageBox *box=new QMessageBox();
    box->setWindowIcon(ico_bad);
    box->setIconPixmap(*map);
    box->setText("Не все поля заполнены");
    box->setWindowTitle("Ошибка");
    box->setStyleSheet("QMessageBox {background-color: rgb(255, 128, 128);"
                       "font: 87 28pt \"Segoe UI Black\";"
                       "color: rgb(0, 0, 0);};");


    QMessageBox *box_ok=new QMessageBox;
    QIcon ico_ok(":/new/images/Materials/Icons 32x32/cool4.ico");
    QPixmap *map1=new QPixmap(":/new/images/Materials/Icons 32x32/cool3.png");
    box_ok->setIconPixmap(*map1);
    box_ok->setWindowTitle("");
    box_ok->setWindowIcon(ico_ok);
    box_ok->setText("Успешно!");
    box->setStyleSheet("QMessageBox {background-color: rgb(177, 255, 176);"
                       "font: 87 28pt \"Segoe UI Black\";"
                       "color: rgb(0, 0, 0);};");


    QDate dateEnd;
    QString name,fatherName,surname,age,pasport,number,gender,dateBuy_str,dateEnd_str;
    name=ui->name->text();
    surname=ui->surname->text();
    fatherName=ui->fatherName->text();
    age=ui->age->text();
    pasport=ui->pasport->toPlainText();

    number=ui->phoneNumber->text();
    dateBuy_str=ui->dateBuy->date().toString(Qt::ISODate);
    if (ui->male_box->checkState()==Qt::Checked)
    {
        gender="М";
    }
    else
    {
        gender="Ж";
    }

    dateEnd=ui->dateBuy->date();
    if(ui->twoYears->isChecked())
    {
        dateEnd=dateEnd.addYears(2);
    }
    else if (ui->oneYear->isChecked())
    {
        dateEnd=dateEnd.addYears(1);
    }
    else if (ui->sixMonths->isChecked())
    {
        dateEnd=dateEnd.addMonths(6);
    }
    else if (ui->threeMonths->isChecked())
    {
        dateEnd=dateEnd.addMonths(3);
    }
    else if (ui->oneMonth->isChecked())
    {
        dateEnd=dateEnd.addMonths(1);
    }

    dateEnd_str=dateEnd.toString(Qt::ISODate);
    if ((name=="")||(surname=="")||(fatherName=="")||(age=="")||(gender=="")||(pasport=="")||(number=="")||(dateEnd_str==""))
    {
        box->exec();
    }
    else
    {
        QString cmd="INSERT INTO clients_info(name,surname,fatherName,age,gender,date_buy,date_end,pasport,avatar,phoneNumber)"
                "VALUES ('"+name+"','"+surname+"','"+fatherName+"',"+age+",'"+gender+"','"+dateBuy_str+"','"+dateEnd_str+"','"+pasport+"','"+cur_image+"','"+number+"');";
        if (!q->exec(cmd))
        {
            qDebug()<<"ошибка опроса"<<cmd;
        }
        else
        {
            qDebug()<<"ok "<<cmd;
            box_ok->exec();
            this->hide();
        }
    }
    delete box;
    delete box_ok;
    qDebug()<<name<<"\n"<<surname<<"\n"<<fatherName<<"\n"<<age<<"\n"<<gender<<"\n"<<pasport<<"\n"<<number<<"\n"<<dateBuy_str<<"\n"<<dateEnd_str<<"\n"<<cur_image;

}
void Add_client::fillData(QSqlDatabase *data)
{
    m_db=new QSqlDatabase(*data);
    q=new QSqlQuery(*m_db);
}

void Add_client::on_male_box_stateChanged(int arg1)
{
    QElapsedTimer t;
    t.start();
    if (arg1)
    {
        ui->female_box->setCheckState(Qt::Unchecked);
        int idx=gen_num(t,0,7);
        QString image_name=getMImage(idx);
        cur_image=":/avas/m/Materials/avatar/men/"+image_name;
        ui->graphicsView->setStyleSheet("QGraphicsView {background-image:url("+cur_image+")};");
    }
    else
    {
         ui->graphicsView->setStyleSheet("QGraphicsView {background-image:url(:/new/no_image/Materials/avatar/no_image.png)};");
    }

}

void Add_client::on_female_box_stateChanged(int arg1)
{
    QElapsedTimer t;
    t.start();
    if (arg1)
    {
        ui->male_box->setCheckState(Qt::Unchecked);
        int idx=gen_num(t,0,8);
        QString image_name=getFImage(idx);
        cur_image=":/avas/w/Materials/avatar/women/"+image_name;
        ui->graphicsView->setStyleSheet("QGraphicsView {background-image:url("+cur_image+")};");
    }
    else
    {
         ui->graphicsView->setStyleSheet("QGraphicsView {background-image:url(:/new/no_image/Materials/avatar/no_image.png)};");
    }


}
QString Add_client::getMImage(int idx)
{
    if ((idx>-1)&&(idx<male_images.size()))
    {
        return male_images[idx];
    }
    else
    {
        qDebug()<<"Плохо:в male_image выход за пределы массива";
        return "";
    }

}
QString Add_client::getFImage(int idx)
{
    if ((idx>-1)&&(idx<female_images.size()))
    {
        return female_images[idx];
    }
    else
    {
        qDebug()<<"Плохо:в female_image выход за пределы массива";
        return "";
    }
}
