#ifndef DIALOGEMPLOYSTUFF_H
#define DIALOGEMPLOYSTUFF_H

#include <QDialog>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QDate>

namespace Ui {
class DialogEmployStuff;
}

class DialogEmployStuff : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEmployStuff(QWidget *parent = nullptr,QSqlDatabase *data=nullptr,QString serviseName="",QString price="",QString date="");
    ~DialogEmployStuff();

private slots:
    void on_ok_clicked();

private:
    QString m_servName;
    QString m_price;
    QString m_date;

    Ui::DialogEmployStuff *ui;

    QSqlDatabase *m_db;
    QSqlQuery *q;

};

#endif // DIALOGEMPLOYSTUFF_H
