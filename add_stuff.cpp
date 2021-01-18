#include "add_stuff.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include "autorization.h"
#include "add_manager.h"
#include "add_medstuff.h"
#include "add_trainer.h"
#include <QDebug>

Add_stuff::Add_stuff(QWidget *parent,QSqlDatabase *data,stuff_type type):QWidget(parent)
{
    m_db=new QSqlDatabase(*data);
    q=new QSqlQuery(*m_db);
    cur_type=type;

    if (cur_type==MANAGER)
    {
        new_manager=new Add_manager(nullptr,m_db);
        new_manager->show();
    }
    if (cur_type==TRAINER)
    {
        new_trainer=new Add_trainer(nullptr,m_db);
        new_trainer->show();
    }
    if (cur_type==MEDSTUFF)
    {
        new_med=new Add_medStuff(nullptr,m_db);
        new_med->show();
    }
}

Add_stuff::~Add_stuff()
{
    delete m_db;
    delete q;
    if (new_manager!=nullptr)
    {
        delete new_manager;
    }
    if (new_med!=nullptr)
    {
        delete new_med;
    }
}
