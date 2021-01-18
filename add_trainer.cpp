#include "add_trainer.h"
#include "ui_add_trainer.h"
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QString>
#include <QDate>
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QDebug>
#include <QVector>
#include <Tuple_gen.h>
#include <QElapsedTimer>

QVector<QString> Add_trainer::male_images={"ava1.png","ava2.png","ava3.png","ava4.png","ava5.png","ava6.png","ava7.png","ava8.png"};
QVector<QString> Add_trainer::female_images={"ava1.png","ava2.png","ava3.png","ava4.png","ava5.png","ava6.png","ava7.png","ava8.png","ava9.png"};

Add_trainer::Add_trainer(QWidget *parent,QSqlDatabase *data) :
    QWidget(parent),
    ui(new Ui::Add_trainer)
{
    ui->setupUi(this);
    ui->image->setStyleSheet("QGraphicsView {background-image:url(:/new/no_image/Materials/avatar/no_image.png)};");
    m_db=new QSqlDatabase(*data);
    q=new QSqlQuery(*m_db);

}

void Add_trainer::on_add_m_clicked()
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
    box_ok->setStyleSheet("QMessageBox {background-color: rgb(177, 255, 176);"
                       "font: 87 28pt \"Segoe UI Black\";"
                       "color: rgb(0, 0, 0);};");


   // QDate dateReg;
    QString name,fatherName,surname,age,pasport,number,gender,dateRegistration,salary,cmd="";
    int new_trainer_id;
    name=ui->name->text();
    surname=ui->surname->text();
    fatherName=ui->fatherName->text();
    age=ui->age->text();
    pasport=ui->pasport->toPlainText();
    salary=ui->salary->text();

    number=ui->phoneNumber->text();
    dateRegistration=ui->dateReg->date().toString(Qt::ISODate);
    if (ui->male_box->checkState()==Qt::Checked)
    {
        gender="М";
    }
    else if (ui->female_box->checkState()==Qt::Checked)
    {
        gender="Ж";
    }



    if ((name=="")||(surname=="")||(fatherName=="")||(age=="")||(gender=="")||(pasport=="")||(number=="")||(salary==""))
    {
        box->exec();
    }
    else
    {
        cmd="INSERT INTO trainers_info(name,surname,fatherName,age,salary,gender,avatar)"
                    "VALUES ('"+name+"','"+surname+"','"+fatherName+"',"+age+","+salary+",'"+gender+"','"+cur_image+"');";
        if (!q->exec(cmd))
        {
            qDebug()<<"ошибка опроса 1"<<cmd;
        }
        else
        {
            qDebug()<<"ok "<<cmd;
            cmd="SELECT max(t_id) FROM trainers_info;";
            if (!q->exec(cmd))
            {
                qDebug()<<"ошибка опроса 2"<<cmd;
            }
            else
            {
                q->next();
                QSqlRecord rec=q->record();
                new_trainer_id=rec.value(0).toInt();
                qDebug()<<new_trainer_id;
                if (ui->mon->checkState()==Qt::Checked)
                {
                     cmd="INSERT INTO trainer_work_days VALUES ("+QString().setNum(new_trainer_id)+","+QString().setNum(0)+");";
                     if (!q->exec(cmd))qDebug()<<"ошибка опроса 3"<<cmd;
                }
                if (ui->tues->checkState()==Qt::Checked)
                {
                    cmd="INSERT INTO trainer_work_days VALUES ("+QString().setNum(new_trainer_id)+","+QString().setNum(1)+");";
                    if (!q->exec(cmd))qDebug()<<"ошибка опроса 4"<<cmd;
                }
                if (ui->wed->checkState()==Qt::Checked)
                {
                    cmd="INSERT INTO trainer_work_days VALUES ("+QString().setNum(new_trainer_id)+","+QString().setNum(2)+");";
                    if (!q->exec(cmd))qDebug()<<"ошибка опроса 4"<<cmd;
                }
                if (ui->thurs->checkState()==Qt::Checked)
                {
                    cmd="INSERT INTO trainer_work_days VALUES ("+QString().setNum(new_trainer_id)+","+QString().setNum(3)+");";
                    if (!q->exec(cmd))qDebug()<<"ошибка опроса 4"<<cmd;
                }
                if (ui->fri->checkState()==Qt::Checked)
                {
                    cmd="INSERT INTO trainer_work_days VALUES ("+QString().setNum(new_trainer_id)+","+QString().setNum(4)+");";
                    if (!q->exec(cmd))qDebug()<<"ошибка опроса 4"<<cmd;
                }
                if (ui->sat->checkState()==Qt::Checked)
                {
                    cmd="INSERT INTO trainer_work_days VALUES ("+QString().setNum(new_trainer_id)+","+QString().setNum(5)+");";
                    if (!q->exec(cmd))qDebug()<<"ошибка опроса 4"<<cmd;
                }
                if (ui->sun->checkState()==Qt::Checked)
                {
                    cmd="INSERT INTO trainer_work_days VALUES ("+QString().setNum(new_trainer_id)+","+QString().setNum(6)+");";
                    if (!q->exec(cmd))qDebug()<<"ошибка опроса 4"<<cmd;
                }
                box_ok->exec();
                this->hide();
                delete box;
                delete box_ok;
            }

        }
    }

}


void Add_trainer::on_male_box_stateChanged(int arg1)
{
    QElapsedTimer t;
    t.start();
    if (arg1)
    {
        ui->female_box->setCheckState(Qt::Unchecked);
        int idx=gen_num(t,0,7);
        QString image_name=getMImage(idx);
        cur_image=":/avas/m/Materials/avatar/men/"+image_name;
        ui->image->setStyleSheet("QGraphicsView {background-image:url("+cur_image+")};");
    }
    else
    {
         ui->image->setStyleSheet("QGraphicsView {background-image:url(:/new/no_image/Materials/avatar/no_image.png)};");
    }

}

void Add_trainer::on_female_box_stateChanged(int arg1)
{
    QElapsedTimer t;
    t.start();
    if (arg1)
    {
        ui->male_box->setCheckState(Qt::Unchecked);
        int idx=gen_num(t,0,8);
        QString image_name=getFImage(idx);
        cur_image=":/avas/w/Materials/avatar/women/"+image_name;
        ui->image->setStyleSheet("QGraphicsView {background-image:url("+cur_image+")};");
    }
    else
    {
         ui->image->setStyleSheet("QGraphicsView {background-image:url(:/new/no_image/Materials/avatar/no_image.png)};");
    }


}
QString Add_trainer::getMImage(int idx)
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
QString Add_trainer::getFImage(int idx)
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

Add_trainer::~Add_trainer()
{
    delete ui;
}
