#ifndef MANAGERINFO_H
#define MANAGERINFO_H

#include <QWidget>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>

namespace Ui {
class ManagerInfo;
}

class ManagerInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerInfo(QWidget *parent = nullptr);
    ~ManagerInfo();
    void fillData(QSqlDatabase *db,int id,int work_center);

private:
    Ui::ManagerInfo *ui;
    QSqlDatabase *m_db;
    QSqlQuery *q;
    int ID;
    int m_work_center;
    QString name;
    QString surname;
    QString fatherName;
    QString post;
    QString gender;
    QString avatar;
    int age;
};

#endif // MANAGERINFO_H
