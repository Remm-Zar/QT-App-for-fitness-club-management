#include "autorization.h"
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QtSql/QSqlQuery>
#include <QString>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QBrush>
#include <QImage>
#include <QPalette>
#include <QMessageBox>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include <QKeyEvent>

Autorization::Autorization(QWidget *parent,QSqlQuery *query,const QString &label_purpose): QWidget(parent)
{
    q=new QSqlQuery(*query);
    m_login=new QLineEdit(this);
    m_pass=new QLineEdit(this);
    m_pass->setEchoMode(QLineEdit::Password);
    m_purpouse=new QLabel(label_purpose);
    m_title=new QLabel("CLUB POWER");
    m_title->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    QLabel *mark_login=new QLabel("Login"),*mark_pass=new QLabel("Password");
    //set styles
    mark_login->setStyleSheet("QLabel {font: 63 12pt \"Segoe UI Semibold\"; color: rgb(255, 255, 255);background-color: rgba(255, 255, 0, 80);};");
    mark_pass->setStyleSheet("QLabel {font: 63 12pt \"Segoe UI Semibold\"; color: rgb(255, 255, 255);background-color: rgba(255, 255, 0, 80);};");
    m_purpouse->setStyleSheet("QLabel {font: 20pt \"Impact\";color: rgb(255, 255, 255);background-color: rgba(255, 255, 0, 80);};");
    m_title->setStyleSheet("QLabel {font: 87 72pt \"Source Serif Pro Black\";color: rgb(255, 255, 255);background-color: rgba(170, 255, 127, 80);};");
    //layouts
    QFormLayout *autorize_layout=new QFormLayout;
    QHBoxLayout *hbox=new QHBoxLayout(),*outHbox=new QHBoxLayout(this);
    QVBoxLayout *vbox=new QVBoxLayout();
    QSpacerItem *space=new QSpacerItem(100,100,QSizePolicy::Expanding),*space1=new QSpacerItem(100,200),*space2=new QSpacerItem(100,20);
    //button style
    m_autorize_button=new QPushButton("Autorization",this);
    m_autorize_button->setStyleSheet("QPushButton {background-color: qlineargradient(spread:repeat, x1:0, y1:0, x2:1, y2:1, stop:0.455056 rgba(255, 255, 255, 237), stop:1 rgba(0, 0, 0, 191));color: rgb(0, 0, 0);font: 11pt \"Noto Sans Arabic UI\";}");
    m_autorize_button->setFixedSize(250,30);

    autorize_layout->setLabelAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
    autorize_layout->addWidget(m_purpouse);
    autorize_layout->addRow(mark_login,m_login);
    autorize_layout->addRow(mark_pass,m_pass);
    //button
    hbox->addWidget(m_autorize_button,1,Qt::AlignHCenter);
    autorize_layout->addItem(space2);
    autorize_layout->addItem(hbox);

    //autorization area
    vbox->addSpacerItem(space);
    vbox->addWidget(m_title,1,Qt::AlignHCenter);
    vbox->addSpacerItem(space1);
    vbox->addLayout(autorize_layout,1);
    vbox->addSpacerItem(space);

    //main layout
    outHbox->addSpacerItem(space);
    outHbox->addLayout(vbox);
    outHbox->addSpacerItem(space);

    setLayout(outHbox);

    connect(m_autorize_button,&QPushButton::clicked, this, &Autorization::check_autorization);
    connect(this,SIGNAL(enter_clicked()),this,SLOT(check_autorization()));

    QWidget::setFocusPolicy(Qt::ClickFocus);
    setFocus();


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
}

void Autorization::check_autorization()
{
    QString login=m_login->text(),pass=m_pass->text();
    QString cmd="SELECT m_id,name,surname FROM managers_info WHERE login='"+login+"' AND password='"+pass+"';";
    if (!q->exec(cmd))
    {
        qDebug()<<"query error: data: "<<login<<" "<<pass<<"\n"<<"cmd:"<<cmd;
    }
    else
    {
        q->next();
        QSqlRecord rec=q->record();
        int ID=rec.value(0).toInt();
        QString name=rec.value(1).toString(),surname=rec.value(2).toString();
        if (!name.isEmpty())
        {
            cmd="SELECT c_id FROM manager_club WHERE m_id="+QString::number(ID)+";";
            if (!q->exec(cmd))
            {
                qDebug()<<"query error: data: "<<login<<" "<<pass<<"\n"<<"cmd:"<<cmd;
            }
            else
            {
                q->next();
                QSqlRecord rec=q->record();
                int work_center=rec.value(0).toInt();
                emit autorize_result(name,surname,ID,work_center);
            }
        }
        else
        {
            QMessageBox *box=new QMessageBox(QMessageBox::Critical,"Ошибка","Неправильный логин/пароль",QMessageBox::Button::Ok);
            box->exec();
            delete box;
        }
    }
}

Autorization::~Autorization()
{

}
/*void Autorization::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Escape)
    {
        QWidget::keyPressEvent(event);
    }
}*/
