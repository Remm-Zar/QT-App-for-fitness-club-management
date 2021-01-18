#include "main_handler.h"
#include "autorization.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>
#include "mainwidget.h"
#include <QIcon>


Main_handler::Main_handler()
{
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QPSQL");
    dataBase.setDatabaseName("fn1133_2020");
    dataBase.setUserName("student");
    dataBase.setHostName("195.19.32.74");
    dataBase.setPassword("bmstu");
    dataBase.setPort(5432);
    if (!  dataBase.open())
    {
        QMessageBox *errBox=new QMessageBox(QMessageBox::Critical,"Error","didn't manage to open database");
        qDebug()<<dataBase.lastError().text();
        errBox->exec();
    }

   query=new QSqlQuery(dataBase);
   m_autorize_widget=new Autorization(0,query,"SIGN-IN");
   m_mw=new MainWidget;
   connect(m_autorize_widget,SIGNAL(autorize_result(QString,QString,int,int)),this,SLOT(success_autorization(QString,QString,int,int)));
   m_autorize_widget->resize(1990,1500);
   m_autorize_widget->show();
}
void Main_handler::success_autorization(QString name,QString surname,int ID,int work_center)
{
    QIcon *icon=new QIcon(":/new/images/Materials/Icons 32x32/man.ico");
     QMessageBox *box=new QMessageBox;
     box->setIconPixmap(QPixmap(":/new/images/Materials/Icons 32x32/man.ico"));
     box->setWindowIcon(*icon);
     box->setStyleSheet("background-color: rgb(203, 255, 238);color: rgb(0, 0, 0);font: 75 14pt \"Marquisette BTN\";");
     box->setText("Здравствуйте, "+surname+" "+name);
     box->setWindowTitle("Успешная авторизация");
     box->exec();
     m_autorize_widget->hide();
     m_mw->fillData(&dataBase,ID,work_center);
     m_mw->resize(1990,1500);
     m_mw->show();
     delete box;
}
Main_handler::~Main_handler()
{
    delete m_autorize_widget;
  //  delete m_mw;
}
