#ifndef TUPLE_GEN_H
#define TUPLE_GEN_H
#include <QString>
#include <QtSql/QSqlQuery>
#include <QElapsedTimer>
#include <vector>
using namespace std;

QString gen_char(QElapsedTimer &time);
QString gen_str(QElapsedTimer &time);
QString gen_date_series(QElapsedTimer &time);
int gen_num(QElapsedTimer &time,int from,int to);
//QString gen_str_arr(QElapsedTimer &time);
//QString gen_str_arr(QString fileName,QElapsedTimer &time,bool repeat);
QVector<QString> gen_artists(int amount,QVector<QString> &artNames);
bool gen_tuple_poster(int amount,QSqlQuery *q);
bool gen_tuple_id_artists(int amount,QSqlQuery *q);
bool gen_tuple_artists(int amount,QSqlQuery *q);

#endif // TUPLE_GEN_H
