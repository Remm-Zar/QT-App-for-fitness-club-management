#ifndef ADD_CLIENT_H
#define ADD_CLIENT_H

#include <QWidget>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QVector>


namespace Ui {
class Add_client;
}

class Add_client : public QWidget
{
    Q_OBJECT

public:
    explicit Add_client(QWidget *parent = nullptr);
    ~Add_client();
    void fillData(QSqlDatabase *data);
    static QString getMImage(int idx);
    static QString getFImage(int idx);
private:
    QSqlDatabase *m_db;
    QSqlQuery *q;
    static QVector<QString> male_images;
    static QVector<QString> female_images;
    QString cur_image;

private slots:
    void on_pushButton_clicked();

    void on_male_box_stateChanged(int arg1);

    void on_female_box_stateChanged(int arg1);

private:
    Ui::Add_client *ui;
};


#endif // ADD_CLIENT_H
