#ifndef STUFFLIST_H
#define STUFFLIST_H

#include <QWidget>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>

namespace Ui {
class StuffList;
}

class StuffList : public QWidget
{
    Q_OBJECT

public:
    enum stuff_type
    {
        NO_TYPE,
        TRAINER,
        MEDSTUFF
    };
    explicit StuffList(QWidget *parent = nullptr,QSqlDatabase *data=nullptr,stuff_type type=NO_TYPE);
    ~StuffList();

private:
    Ui::StuffList *ui;
    QSqlDatabase *m_db;
    QSqlQuery *q;
};

#endif // STUFFLIST_H
