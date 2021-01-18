#ifndef ADD_MANAGER_H
#define ADD_MANAGER_H

#include <QWidget>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QVector>

namespace Ui {
class Add_manager;
}

class Add_manager : public QWidget
{
    Q_OBJECT

public:
    explicit Add_manager(QWidget *parent = nullptr,QSqlDatabase *data=nullptr);
    ~Add_manager();

    //void fillData(QSqlDatabase *data);
    static QString getMImage(int idx);
    static QString getFImage(int idx);

private slots:
    void on_add_m_clicked();

    void on_male_box_stateChanged(int arg1);

    void on_female_box_stateChanged(int arg1);


private:
    Ui::Add_manager *ui;
    QSqlDatabase *m_db;
    QSqlQuery *q;
    static QVector<QString> male_images;
    static QVector<QString> female_images;
    QString cur_image;
};

#endif // ADD_MANAGER_H
