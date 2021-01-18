#include "add_manager.h"
#include "ui_add_manager.h"
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
#include <QtSql/QSqlRecord>



QVector<QString> Add_manager::male_images={"ava1.png","ava2.png","ava3.png","ava4.png","ava5.png","ava6.png","ava7.png","ava8.png"};
QVector<QString> Add_manager::female_images={"ava1.png","ava2.png","ava3.png","ava4.png","ava5.png","ava6.png","ava7.png","ava8.png","ava9.png"};

Add_manager::Add_manager(QWidget *parent,QSqlDatabase *data) :
    QWidget(parent),
    ui(new Ui::Add_manager)
{
    ui->setupUi(this);
    ui->image->setStyleSheet("QGraphicsView {background-image:url(:/new/no_image/Materials/avatar/no_image.png)};");
    m_db=new QSqlDatabase(*data);
    q=new QSqlQuery(*m_db);
}

Add_manager::~Add_manager()
{
    delete m_db;
    delete q;
    delete ui;
}
void Add_manager::on_add_m_clicked()
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


   // QDate dateReg;
    QString name,fatherName,surname,age,pasport,number,gender,work_center,dateRegistration,salary,post,login,pass;
    name=ui->name->text();
    surname=ui->surname->text();
    fatherName=ui->fatherName->text();
    age=ui->age->text();
    pasport=ui->pasport->toPlainText();
    salary=ui->salary->text();
    login=ui->login->text();
    pass=ui->password->text();
    post=ui->post->text();
    work_center=ui->workCenter->text();

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
    if ((name=="")||(surname=="")||(fatherName=="")||(age=="")||(gender=="")||(pasport=="")||(number=="")||(salary=="")||(post=="")||(login=="")||(pass==""))
    {
        box->exec();
    }
    else
    {
        QString cmd="INSERT INTO managers_info(post,name,surname,fatherName,age,salary,gender,avatar,login,password)"
                    "VALUES ('"+post+"','"+name+"','"+surname+"','"+fatherName+"',"+age+","+salary+",'"+gender+"','"+cur_image+"','"+login+"','"+pass+"');";
        if (!q->exec(cmd))
        {
            qDebug()<<"ошибка опроса"<<cmd;
        }
        else
        {
            qDebug()<<"ok "<<cmd;
            cmd="SELECT m_id FROM managers_info WHERE login='"+login+"' AND password='"+pass+"';";
            if (!q->exec(cmd))
            {
                qDebug()<<"ошибка опроса"<<cmd;
            }
            else
            {
                q->next();
                QSqlRecord rec=q->record();
                int m_id=rec.value(0).toInt();
                cmd="INSERT INTO manager_club VALUES("+QString::number(m_id)+","+work_center+");";
                if (!q->exec(cmd))
                {
                    qDebug()<<"ошибка опроса"<<cmd;
                }
                else
                {
                    box_ok->exec();
                   this->hide();
                }
            }
        }
    }
    delete box;
    delete box_ok;
}
void Add_manager::on_male_box_stateChanged(int arg1)
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

void Add_manager::on_female_box_stateChanged(int arg1)
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
QString Add_manager::getMImage(int idx)
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
QString Add_manager::getFImage(int idx)
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

