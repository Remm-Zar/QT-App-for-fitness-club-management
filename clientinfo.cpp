#include "clientinfo.h"
#include "ui_clientinfo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QStringList>

ClientInfo::ClientInfo(QWidget *parent,QSqlDatabase *data,int id) :
    QWidget(parent),
    ui(new Ui::ClientInfo)
{
    ui->setupUi(this);
    db=new QSqlDatabase(*data);
    q=new QSqlQuery(*db);
    ID=id;
    QString cmd="SELECT date,service_name,price FROM client_hist WHERE c_id="+QString::number(id)+";";
    if (!q->exec(cmd))
    {
        qDebug()<<"error";
    }
    else
    {
        QStringList list={"Дата","Услуга","Цена"};
        QSqlQueryModel *model=new QSqlQueryModel;
        model->setQuery(*q);
        model->setParent(ui->tableView);
        ui->tableView->setModel(model);
        ui->tableView->horizontalHeader()->setFixedHeight(30);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        cmd="SELECT name,surname,fatherName,age,gender,avatar FROM clients_info WHERE c_id="+QString::number(ID)+";";
        if (!q->exec(cmd))
        {
            qDebug()<<"error";
        }
        else
        {
            q->next();
            QSqlRecord rec=q->record();
            QString name=rec.value(0).toString(),surname=rec.value(1).toString(),fatherName=rec.value(2).toString();
            QString gender=rec.value(4).toString(),avatar=rec.value(5).toString();
            int age=rec.value(3).toInt();

            qDebug()<<avatar;

            ui->name->insert(name);
            ui->surname->insert(surname);
            ui->fatherName->insert(fatherName);
            ui->age->insert(QString::number(age));
            ui->gender->insert(gender);
            ui->image->setStyleSheet("QListView {background-image: url("+avatar+")};");
        }
    }
}

ClientInfo::~ClientInfo()
{
    delete ui;
}
