#ifndef ADD_STUFF_H
#define ADD_STUFF_H
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include "add_manager.h"
#include "add_medstuff.h"
#include "add_trainer.h"

class Add_stuff: public QWidget
{
    Q_OBJECT
public:
    enum stuff_type
    {
        NO_TYPE,
        MANAGER,
        TRAINER,
        MEDSTUFF
    };
    explicit Add_stuff(QWidget *parent = nullptr,QSqlDatabase *data=nullptr,stuff_type type=NO_TYPE);
    ~Add_stuff();
private:
    QSqlDatabase *m_db;
    QSqlQuery *q;
    Add_manager *new_manager;
    Add_medStuff *new_med;
    Add_trainer *new_trainer;
    stuff_type cur_type;
};

#endif // ADD_STUFF_H
