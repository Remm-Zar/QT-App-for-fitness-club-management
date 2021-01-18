#ifndef ADD_TRAINER_H
#define ADD_TRAINER_H

#include <QWidget>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QVector>

namespace Ui {
class Add_trainer;
}

class Add_trainer : public QWidget
{
    Q_OBJECT

public:
    explicit Add_trainer(QWidget *parent = nullptr,QSqlDatabase *data=nullptr);
    ~Add_trainer();

    static QString getMImage(int idx);
    static QString getFImage(int idx);
private slots:
    void on_male_box_stateChanged(int arg1);
    void on_female_box_stateChanged(int arg1);
    void on_add_m_clicked();
private:
    Ui::Add_trainer *ui;
    QSqlDatabase *m_db;
    QSqlQuery *q;
    static QVector<QString> male_images;
    static QVector<QString> female_images;
    QString cur_image;
};

#endif // ADD_TRAINER_H
