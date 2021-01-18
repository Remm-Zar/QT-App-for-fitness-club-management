#ifndef ADD_MEDSTUFF_H
#define ADD_MEDSTUFF_H

#include <QWidget>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QVector>

namespace Ui {
class Add_medStuff;
}

class Add_medStuff : public QWidget
{
    Q_OBJECT

public:
    explicit Add_medStuff(QWidget *parent = nullptr,QSqlDatabase *data=nullptr);
    ~Add_medStuff();

    static QString getMImage(int idx);
    static QString getFImage(int idx);
private slots:
    void on_male_box_stateChanged(int arg1);
    void on_female_box_stateChanged(int arg1);
    void on_add_m_clicked();

private:
    Ui::Add_medStuff *ui;
    QSqlDatabase *m_db;
    QSqlQuery *q;
    static QVector<QString> male_images;
    static QVector<QString> female_images;
    QString cur_image;
};

#endif // ADD_MEDSTUFF_H
