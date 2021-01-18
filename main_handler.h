#ifndef MAIN_HANDLER_H
#define MAIN_HANDLER_H

#include <QObject>
#include "autorization.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "mainwidget.h"

class Main_handler: public QObject
{
    Q_OBJECT
public:
    Main_handler();
    ~Main_handler();
private:
    QSqlDatabase dataBase;
    QSqlQuery *query;
    Autorization *m_autorize_widget;
    MainWidget *m_mw;

private slots:
    void success_autorization(QString name,QString surname,int ID,int work_center);
    friend class Autorization;
};

#endif // MAIN_HANDLER_H
