#include "dialogemploystuff.h"
#include "ui_dialogemploystuff.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QDebug>

DialogEmployStuff::DialogEmployStuff(QWidget *parent,QSqlDatabase *data,QString serviseName,QString price,QString date) :
    QDialog(parent),
    ui(new Ui::DialogEmployStuff)
{
    ui->setupUi(this);
    m_db=new QSqlDatabase(*data);
    q=new QSqlQuery(*m_db);
    m_servName=serviseName;
    m_price=price;
    m_date=date;
    ui->service->insert(serviseName);
    ui->price->insert(price);
}

DialogEmployStuff::~DialogEmployStuff()
{
    delete ui;
}

void DialogEmployStuff::on_ok_clicked()
{
    QString ID=ui->clientID->text();
    QString cmd="INSERT INTO client_hist(c_id,date,service_name,price) VALUES("+ID+",'"+m_date+"','"+m_servName+"',"+m_price+");";

    if (!q->exec(cmd))
    {
        qDebug()<<"чёт не так"<<cmd;
    }
    this->hide();
}
