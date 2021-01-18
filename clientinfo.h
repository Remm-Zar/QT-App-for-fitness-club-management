#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <QWidget>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>

namespace Ui {
class ClientInfo;
}

class ClientInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ClientInfo(QWidget *parent = nullptr,QSqlDatabase *data=nullptr,int id=-1);
    ~ClientInfo();

private:
    Ui::ClientInfo *ui;
    QSqlDatabase *db;
    QSqlQuery *q;
    int ID;
};

#endif // CLIENTINFO_H
