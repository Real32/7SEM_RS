#include <QCoreApplication>
#include "dbmanager.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DBManager db;
//    db.createTableUser("hero1");
//    db.insertLogin("hero1", "login/r/n");
//    db.insertLogin("hero1", "login2/r/n");
//    db.insertLogin("hero1", "login3/r/n");
//    db.insertPassword("hero1", "password/r/n");
    qDebug()<<db.getPassword("hero1");
    db.updateFriend("hero1");
    return a.exec();
}
