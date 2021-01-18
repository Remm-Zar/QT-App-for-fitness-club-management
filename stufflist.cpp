#include "stufflist.h"
#include "ui_stufflist.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QString>
#include <QDebug>

StuffList::StuffList(QWidget *parent,QSqlDatabase *data,stuff_type type) :
    QWidget(parent),
    ui(new Ui::StuffList)
{
    ui->setupUi(this);
    m_db=new QSqlDatabase(*data);
    q=new QSqlQuery(*m_db);
    QString cmd;
    if (type==TRAINER)
    {
        this->setWindowIcon(QIcon(":/new/images/Materials/Icons 32x32/sport.ico"));
        this->setWindowTitle("Тренеры");
        cmd="SELECT name,surname,fatherName,t_id FROM trainers_info;";
        if (!q->exec(cmd))
        {
            qDebug()<<"trainer query error: "<<cmd;
        }
        else
        {
            ui->label->setText("Команда Тренеров");
            ui->tableWidget->setColumnCount(4);
            ui->tableWidget->setShowGrid(true);
            ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            QColor color(255, 255, 255, 200);

            for (int i=0;q->next();++i)
            {
                ui->tableWidget->insertRow(i);
                if (i==0)
                {
                    ui->tableWidget->setItem(0,0,new QTableWidgetItem("Имя"));
                    ui->tableWidget->setItem(0,1,new QTableWidgetItem("Фамилия"));
                    ui->tableWidget->setItem(0,2,new QTableWidgetItem("Отчество"));
                    ui->tableWidget->setItem(0,3,new QTableWidgetItem("ID"));
                }
                else
                {
                    for (int j=0;j<5;++j)
                    {
                        ui->tableWidget->setItem(i,j,new QTableWidgetItem(q->value(j).toString()));
                       // ui->tableWidget->item(i,j)->setBackground(color);
                    }
                }

            }
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableWidget->setColumnHidden(4,true);
        }

    }

    if (type==MEDSTUFF)
    {
        this->setWindowIcon(QIcon(":/new/images/Materials/Icons 32x32/med.ico"));
        this->setWindowTitle("Мед-персонал");
        cmd="SELECT name,surname,fatherName,med_id FROM med_info;";
        if (!q->exec(cmd))
        {
            qDebug()<<"trainer query error: "<<cmd;
        }
        else
        {
            ui->label->setText("Команда медиков");
            ui->tableWidget->setColumnCount(4);
            ui->tableWidget->setShowGrid(true);
            ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            QColor color(255, 255, 255, 200);
            for (int i=0;q->next();++i)
            {
                ui->tableWidget->insertRow(i);
                ui->tableWidget->insertRow(i);
                if (i==0)
                {
                    ui->tableWidget->setItem(0,0,new QTableWidgetItem("Имя"));
                    ui->tableWidget->setItem(0,1,new QTableWidgetItem("Фамилия"));
                    ui->tableWidget->setItem(0,2,new QTableWidgetItem("Отчество"));
                    ui->tableWidget->setItem(0,3,new QTableWidgetItem("ID"));
                }
                for (int j=0;j<4;++j)
                {
                    ui->tableWidget->setItem(i,j,new QTableWidgetItem(q->value(j).toString()));
                    //ui->tableWidget->item(i,j)->setBackground(color);
                }
            }
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableWidget->setColumnHidden(3,true);
        }
    }
}

StuffList::~StuffList()
{
    delete ui;
}
