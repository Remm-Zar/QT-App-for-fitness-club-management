#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <managerinfo.h>
#include "stufflist.h"
#include <add_client.h>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QString>
#include <QDebug>
#include <QBrush>
#include <QImage>
#include <QPalette>
#include <QMessageBox>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include "add_stuff.h"
#include <QException>
#include <QLocale>
#include <QDate>
#include <QTableWidgetItem>
#include <QColor>
#include <QtSql/QSqlQueryModel>
#include "dialogemploystuff.h"
#include "clientinfo.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    qDebug()<<"SetUp\n";
    ui->setupUi(this);
   // m_db=new QSqlDatabase;
   // q=nullptr;
    card=new ManagerInfo;
    //background
    QImage *image=new QImage(":/new/Materials/Backgrounds/back_2.jpg");
    image->scaled(Qt::WindowFullScreen,Qt::KeepAspectRatioByExpanding);
    QBrush *brush=new QBrush;
    QPalette *palette=new QPalette;
    this->setAutoFillBackground(true);
    brush->setTextureImage(*image);
    palette->setBrush(QPalette::Background,*brush);
    this->setPalette(*palette);
    delete image;
    delete brush;

    //icons
    QIcon addStuff_ico(":/new/images/Materials/Icons 32x32/add user.ico");
    QIcon addClient_ico(":/new/images/Materials/Icons 32x32/client.ico");
    QIcon managerInfo_ico(":/new/images/Materials/Icons 32x32/avatar2.png");
    QIcon trenersList_ico(":/new/images/Materials/Icons 32x32/sport.ico");
    QIcon medList_ico(":/new/images/Materials/Icons 32x32/med.ico");
    QIcon full_schedule_ico(":/new/images/Materials/Icons 32x32/calendar 2.ico");
    QIcon help_ico(":/new/images/Materials/Icons 32x32/balloon.ico");
    QIcon addTrainer_ico(":/new/images/Materials/Icons 32x32/addTrainer.ico");
    QIcon addMedStuff_ico(":/new/images/Materials/Icons 32x32/addMedStuff.ico");

    //MenuBar
    QMenuBar *menuBar=new QMenuBar(this);
    QMenu *add_person=new QMenu("&Добавить"),*team=new QMenu("&Команда");
    QMenu *add_stuff=new QMenu("&Добавить персонал");

    QAction *addClient =new QAction (addClient_ico,"Добавить клиента",this);
    QAction *addManager=new QAction (addStuff_ico,"Добавить менеджера",this);
    QAction *addTrainer=new QAction(addTrainer_ico,"Добавить тренера",this);
    QAction *addMedStuff=new QAction(addMedStuff_ico,"Добавить медперсонал",this);

    QAction *trenersList=new QAction (trenersList_ico,"Тренерский состав",this);
    QAction *medList=new QAction(medList_ico,"Мед персонал этого центра",this);

    add_stuff->addAction(addManager);
    add_stuff->addAction(addTrainer);
    add_stuff->addAction(addMedStuff);

    add_person->addAction(addClient);
    add_person->addMenu(add_stuff);
    team->addAction(trenersList);
    team->addAction(medList);

    menuBar->addMenu(add_person);
    menuBar->addSeparator();
    menuBar->addMenu(team);
    menuBar->setStyleSheet("QMenuBar {background-color: rgba(193, 255, 222, 255);"
                          "border-color: rgb(0, 0, 0);"
                           "font: 63 10pt \"Segoe UI Semibold\";"
                           "border-style:outset;"
                           "border-width:3px;"
                           "border-color:rgb(113, 185, 161)};");
    ui->horizontalLayout_4->addWidget(menuBar,1,Qt::AlignLeft);
    menuBar->show();



    //ToolBar

    QToolBar *toolBar=new QToolBar("toolBar",this);

    toolBar->setMovable(true);
    QAction *managerInfo=new QAction(managerInfo_ico,"Информация о текущем сотруднике",this);
    //QAction *full_schedule=new QAction( full_schedule_ico,"Расписание других центров",this);
    QAction *help=new QAction (help_ico,"Справка",this);

    toolBar->addAction(managerInfo);
    //toolBar->addAction(full_schedule);
    toolBar->addSeparator();
    toolBar->addAction(help);
    toolBar->setIconSize(QSize(30,30));

    ui->horizontalLayout_6->addWidget(toolBar,1,Qt::AlignLeft);
    //clients list
    ui->clientsWiget->setColumnCount(3);
    ui->clientsWiget->setShowGrid(true);
    ui->clientsWiget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->clientsWiget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->clientsWiget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //connections
    connect(managerInfo,&QAction::triggered,this,&MainWidget::show_manager_info);//
    connect(addManager,&QAction::triggered,this,&MainWidget::add_manager);//
    connect(addTrainer,&QAction::triggered,this,&MainWidget::add_trainer);
    connect(addMedStuff,&QAction::triggered,this,&MainWidget::add_med_stuff);//
    connect(addClient,&QAction::triggered,this,&MainWidget::add_client);//
    connect(trenersList,&QAction::triggered,this,&MainWidget::show_treners_list);
    connect(medList,&QAction::triggered,this,&MainWidget::show_med_list);
    connect(this,SIGNAL(fillPriceListByDefault()),this,SLOT(priceListDefault()));
}
void MainWidget::fillData(QSqlDatabase *db,int id,int work_center)
{
    QString cmd;
    m_db=new QSqlDatabase(*db);
    q=new QSqlQuery(*db);
    ID=id;
    m_work_center=work_center;
    card->fillData(m_db,ID,m_work_center);

    //current date
    QLocale engl("English");
    QDate curDate;
    curDate=curDate.currentDate();
    ui->dateEdit->setDate(curDate);

     //address
     cmd="SELECT address FROM clubs_info WHERE club_id="+QString::number(m_work_center)+";";
     QString address;
     if (!q->exec(cmd))
     {
         qDebug()<<"address error "<<cmd;
     }
     else
     {
         q->next();
         QSqlRecord rec=q->record();
         address=rec.value(0).toString();
         ui->address->setText(address);
     }

     //setting qModel
     emit fillPriceListByDefault();
}
void MainWidget::add_manager()
{
    stuff=new Add_stuff(nullptr,m_db,Add_stuff::MANAGER);
}
void MainWidget::add_trainer()
{
    stuff=new Add_stuff(nullptr,m_db,Add_stuff::TRAINER);
}
void MainWidget::add_med_stuff()
{
   stuff=new Add_stuff(nullptr,m_db,Add_stuff::MEDSTUFF);
}

void MainWidget::add_client()
{
    Add_client *new_client=new Add_client;
    new_client->fillData(m_db);
    new_client->show();
}

void MainWidget::show_treners_list()
{
    StuffList *list=new StuffList(nullptr,m_db,StuffList::TRAINER);
    list->show();
}
void MainWidget::show_med_list()
{
    StuffList *list=new StuffList(nullptr,m_db,StuffList::MEDSTUFF);
    list->show();
}

void MainWidget::show_manager_info()
{
    card->show();
}


MainWidget::~MainWidget()
{
        if (card!=nullptr)
        {qDebug()<<"card";
           delete card;

        }
        if (q!=nullptr)
        {qDebug()<<"q";
            delete q;

        }
    delete ui;
}

void MainWidget::on_dateEdit_userDateChanged(const QDate &date)
{
    ui->schedule->setRowCount(0);
    //schedule
    ui->schedule->setColumnCount(5);
    ui->schedule->setShowGrid(true);
    ui->schedule->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->schedule->setSelectionBehavior(QAbstractItemView::SelectRows);

    QLocale engl("English");
    QString dayName=engl.toString(date,"dddd");
    QString cmd="SELECT time,training,t_name,t_surname,t_id FROM "+dayName+" WHERE c_id="+QString::number(m_work_center)+";";
        if (!q->exec(cmd))
        {
            qDebug()<<"schedule error "<<cmd;
        }
        else
        {
            QColor color(255, 255, 255, 200);
            for (int i=0;q->next();++i)
            {
                ui->schedule->insertRow(i);
                for (int j=0;j<5;++j)
                {
                    ui->schedule->setItem(i,j,new QTableWidgetItem(q->value(j).toString()));
                    ui->schedule->item(i,j)->setBackground(color);
                }
            }
        }
        ui->schedule->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->schedule->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->schedule->setColumnHidden(4,true);

}

void MainWidget::on_add_clicked()
{
    QString id=ui->clientID->text();
    QString cmd="SELECT c_id,surname,name FROM clients_info WHERE c_id="+id+";";
    if (!q->exec(cmd))
    {
        qDebug()<<"client error "<<cmd;
    }
    else
    {
        q->next();
        QSqlRecord rec=q->record();
        //int id=rec.value(0).toInt();
        QString name=rec.value(1).toString(),surname=rec.value(2).toString();
        if (!name.isEmpty())
        {
            int rowCount=ui->clientsWiget->rowCount();
            QColor color(255, 255, 255, 200);
                ui->clientsWiget->insertRow(rowCount);
                for (int j=0;j<3;++j)
                {
                    ui->clientsWiget->setItem(rowCount,j,new QTableWidgetItem(q->value(j).toString()));
                    ui->clientsWiget->item(rowCount,j)->setBackground(color);
                }           
            ui->clientsWiget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //ui->clientsWiget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        else
        {
            QPixmap *map=new QPixmap(":/new/images/Materials/Icons 32x32/stop.png");
            QIcon ico_bad(":/new/images/Materials/Icons 32x32/stop.ico");
            QMessageBox *box=new QMessageBox();
            box->setWindowIcon(ico_bad);
            box->setIconPixmap(*map);
            box->setText("Клиент отсутствует в базе");
            box->setWindowTitle("Ошибка");
            box->setStyleSheet("QMessageBox {background-color: rgb(255, 128, 128);"
                               "font: 87 28pt \"Segoe UI Black\";"
                               "color: rgb(0, 0, 0);};");
            box->exec();
            delete box;
        }
    }
}




void MainWidget::on_rm_clicked()
{
    QString id=ui->clientID->text();
    int rows=ui->clientsWiget->rowCount();
    for (int i=0;i<rows;++i)
    {
        if (ui->clientsWiget->item(i,0)->text()==id)
        {
            ui->clientsWiget->removeRow(i);
            i=rows;
        }
    }
}

void MainWidget::on_priceList_clicked(const QModelIndex &index)
{
    QString cmd;
   static QString serviceName,price,date=ui->dateEdit->date().toString(Qt::ISODate);
   QModelIndexList list=ui->priceList->selectionModel()->selectedIndexes();
   qDebug()<<list;
    index.row();

    if (list.size()==3)
    {
        serviceName=list[1].data().toString();
        price=list[2].data().toString();
        int id=list.at(0).data().toInt();
        qDebug()<<serviceName<<" "<<price<<" "<<id;
        switch (id)
        {
        case 1:
        {
            ui->priceList->model()->deleteLater();
            qDebug()<<"model1"<<qModel<<"\n";
            int day=ui->dateEdit->date().dayOfWeek();
            cmd="SELECT trainers_info.t_id,surname,name,status FROM trainers_info INNER JOIN trainer_work_days ON trainers_info.t_id=trainer_work_days.t_id "
                "AND trainer_work_days.dayinweek="+QString::number(day)+";";
            if (!q->exec(cmd))
            {
                qDebug()<<"trainers work today error "<<cmd;
            }
            else
            {
                QSqlQueryModel *qModelTrainers=new QSqlQueryModel;
                qModelTrainers->setQuery(*q);
                qModelTrainers->setParent(ui->priceList);
                ui->priceList->setModel(qModelTrainers);
                ui->priceList->setColumnHidden(0,true);
            }
        }break;
        default:
        {
            DialogEmployStuff *service=new DialogEmployStuff(nullptr,m_db,serviceName,price,date);
            service->show();
        }
        }

    }
    else if (list.size()==4)
    {
        QString name=list[2].data().toString(),surname=list[1].data().toString();
        qDebug()<<name<<" "<<surname;
        QMessageBox *box=new QMessageBox(QMessageBox::Information,"","Нанять тренера: "+surname+" "+name+"?",QMessageBox::Ok|QMessageBox::Cancel);
        int ret=box->exec();
        if (ret==QMessageBox::Ok)
        {
            DialogEmployStuff *service1=new DialogEmployStuff(nullptr,m_db,serviceName,price,date);
            service1->show();
        }
        ui->priceList->model()->deleteLater();
        emit fillPriceListByDefault();
    }
}

void MainWidget::priceListDefault()
{
    qDebug()<<"In price list";
    QString cmd="SELECT * FROM prices;";
    qModel=new QSqlQueryModel;
    if (!q->exec(cmd))
    {
        qDebug()<<"address error "<<cmd;
    }
    else
    {
        qModel->setQuery(*q);
        qModel->setParent(ui->priceList);
    }
    QColor color(255, 255, 255, 200);
    ui->priceList->setModel(qModel);
    ui->priceList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->priceList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->priceList->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->priceList->setColumnHidden(0,true);
}

void MainWidget::on_clientsWiget_cellDoubleClicked(int row, int column)
{
    column=0;
    int id=ui->clientsWiget->item(row,0)->text().toInt();
    ClientInfo *c_i=new ClientInfo(nullptr,m_db,id);
    c_i->show();
}
