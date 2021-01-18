#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QWidget>
#include <QPushButton>
#include <QtSql/QSqlQuery>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QKeyEvent>

class Autorization : public QWidget
{
    Q_OBJECT
public:
    explicit Autorization(QWidget *parent = nullptr,QSqlQuery *query=nullptr,const QString &label_purpose="");
    ~Autorization();

signals:
    void autorize_result(QString,QString,int,int);
    void enter_clicked();

private slots:
    void check_autorization();
protected:
  // virtual void keyPressEvent(QKeyEvent *event);

private:
    QPushButton *m_autorize_button;
    QSqlQuery *q;
    QLineEdit *m_login;
    QLineEdit *m_pass;
    QLabel *m_purpouse;
    QLabel *m_title;

};

#endif // AUTORIZATION_H
