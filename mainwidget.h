#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include "autorization.h"
#include <managerinfo.h>
#include <QtSql/QSqlDatabase>
#include <QString>
#include "add_stuff.h"
#include <QtSql/QSqlQueryModel>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void fillData(QSqlDatabase *db,int id,int work_center);
    void set_id(int id)
    {
        ID=id;
    }
signals:
    void fillPriceListByDefault();
private slots:
    void add_manager();
    void add_trainer();
    void add_med_stuff();
    void add_client();
    void show_treners_list();
    void show_med_list();
    void show_manager_info();
    void on_dateEdit_userDateChanged(const QDate &date);
    void on_add_clicked();
    void on_rm_clicked();
    void on_priceList_clicked(const QModelIndex &index);
    void priceListDefault();

    void on_clientsWiget_cellDoubleClicked(int row, int column);

private:
    Ui::MainWidget *ui;
    Autorization *autoriz;
    ManagerInfo *card;
    Add_stuff *stuff;

    QSqlQuery *q;
    QSqlDatabase *m_db;
    QSqlQueryModel *qModel;

    int ID;
    int m_work_center;

};

#endif // MAINWIDGET_H
