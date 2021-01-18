#include "managerinfo.h"
#include "ui_managerinfo.h"
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

ManagerInfo::ManagerInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerInfo)
{
    ui->setupUi(this);
    q=nullptr;
    m_db=nullptr;
}

ManagerInfo::~ManagerInfo()
{
    delete ui;
}
void ManagerInfo::fillData(QSqlDatabase *db,int id,int work_center)
{
    m_db=new QSqlDatabase(*db);
    q=new QSqlQuery(*m_db);
    ID=id;
    m_work_center=work_center;
   // qDebug()<<"ID from m_info: "<<ID;
    QString cmd="SELECT name,surname,fatherName, post,age,gender,avatar FROM managers_info WHERE m_id="+QString::number(ID)+";";
    if (!q->exec(cmd))
    {
        qDebug()<<q->lastError();
    }
    else
    {
        q->next();
        QSqlRecord rec=q->record();
        name=rec.value(0).toString();
        surname=rec.value(1).toString();
        fatherName=rec.value(2).toString();
        post=rec.value(3).toString();
        age=rec.value(4).toUInt();
        gender=rec.value(5).toString();
        avatar=rec.value(6).toString();
       // qDebug()<<name<<" "<<surname<<" "<<fatherName<<" "<<post<<" "<<age<<" "<<gender<<" "<<avatar;

        ui->post->insert(post);
        ui->name->insert(name);
        ui->surname->insert(surname);
        ui->fatherName->insert(fatherName);
        ui->age->insert(QString::number(age));
        ui->gender->insert(gender);
        ui->workCenter->insert(QString::number(m_work_center));
        ui->image->setStyleSheet("QListView {background-image: url(:/avas/"+avatar+")};");
        //qDebug()<<"QListView {background-image: url(:/avas/"+avatar+")};";
     }
}
