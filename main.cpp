#include "mainwidget.h"
//#include "autorization.h"
#include "main_handler.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setEffectEnabled(Qt::UI_AnimateMenu);
    Main_handler w;
   //  MainWidget w;
   //  w.show();
    return a.exec();
}
