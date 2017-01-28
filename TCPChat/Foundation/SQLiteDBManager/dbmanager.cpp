#include "dbmanager.h"

DBManager::DBManager(QObject *parent) : QObject(parent)
{
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("db_name.db");
    if (!sdb.open()) {
           qDebug() << Q_FUNC_INFO << "Can't open DataBase";
       }
    else{
           qDebug() << Q_FUNC_INFO << "DataBase open success";
           query=new QSqlQuery(sdb);
    }

}

void DBManager::createTableUser(QString username)
{
    // DDL query
    QString str = "CREATE TABLE " + username +" ("
            "login VARCHAR(50), "
            "password VARCHAR(50), "
            "friends VARCHAR(50), "
            "invitesin VARCHAR(50), "
            "invitesout VARCHAR(50)"
            ")";
    qDebug() << str;
    bool result = query->exec(str);
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't CREATE TABLE USERS";
    }

}

void DBManager::insertLogin(QString username, QString login)
{
    //QSqlQuery query;
    query->prepare("INSERT INTO " + username + " (login) "
                  "VALUES (:login)");
    query->bindValue(":login", login);

    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't INSERT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "INSERT LOGIN SUCCESS";
    }
}

void DBManager::insertPassword(QString username, QString password)
{
    query->prepare("INSERT INTO " + username + " (password) "
                  "VALUES (:password)");
    query->bindValue(":password", password);

    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't INSERT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "INSERT PASSWORD SUCCESS";
    }
}

void DBManager::insertFriend(QString username, QString friendname)
{
    query->prepare("INSERT INTO " + username + " (friends) "
                  "VALUES (:friend)");
    query->bindValue(":friend", friendname);

    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't INSERT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "INSERT FRIEND SUCCESS";
    }
}

void DBManager::insertInvitesIn(QString username, QString invitesIN)
{
    query->prepare("INSERT INTO " + username + " (invitesin) "
                  "VALUES (:friend)");
    query->bindValue(":invitesin", invitesIN);

    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't INSERT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "INSERT INVITESIN SUCCESS";
    }
}

void DBManager::insertInvitesOut(QString username, QString invitesOUT)
{
    query->prepare("INSERT INTO " + username + " (invitesout) "
                  "VALUES (:invitesout)");
    query->bindValue(":invitesin", invitesOUT);

    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't INSERT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "INSERT INVITESOUT SUCCESS";
    }
}

QString DBManager::getLogin(QString username)
{
    QString login;
    query->prepare("SELECT login FROM " + username);
    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT LOGIN SUCCESS";
    }
    while (query->next()) {
        login = login + query->value(0).toString();
    }
    return login;
}

QString DBManager::getPassword(QString username)
{
    QString password;
    query->prepare("SELECT password FROM " + username);
    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT PASSWORD SUCCESS";
    }
    while (query->next()) {
        password = password + query->value(0).toString();
    }
    return password;
}

QString DBManager::getFriends(QString username)
{
    QString friends;
    query->prepare("SELECT friends FROM " + username);
    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT FRIEND SUCCESS";
    }
    while (query->next()) {
        friends = friends + query->value(0).toString() + "/r/n";
    }
    return friends;
}

QString DBManager::getInvitesIn(QString username)
{
    QString invitesin;
    query->prepare("SELECT invitesin FROM " + username);
    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT INVITESIN SUCCESS";
    }
    while (query->next()) {
        invitesin = invitesin + query->value(0).toString() + "/r/n";
    }
    return invitesin;
}

QString DBManager::getInvitesOut(QString username)
{
    QString invitesout;
    query->prepare("SELECT invitesout FROM " + username);
    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT INVITESOUT SUCCESS";
    }
    while (query->next()) {
        invitesout = invitesout + query->value(0).toString() + "/r/n";
    }
    return invitesout;
}

void DBManager::updateFriend(QString username)
{
    query->prepare("UPDATE " + username + " SET friends = NULL");
    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't UPDATE";
        }
    else{
        qDebug() << Q_FUNC_INFO << "UPDATE FRIENDS SUCCESS";
    }
}

void DBManager::updateInviteIn(QString username)
{
    query->prepare("UPDATE " + username + " SET invitesin = NULL");
    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't UPDATE";
        }
    else{
        qDebug() << Q_FUNC_INFO << "UPDATE INVITESIN SUCCESS";
    }
}

void DBManager::updateInviteOut(QString username)
{
    query->prepare("UPDATE " + username + " SET invitesout = NULL");
    bool result = query->exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't UPDATE";
        }
    else{
        qDebug() << Q_FUNC_INFO << "UPDATE INVITESOUT SUCCESS";
    }
}

DBManager::~DBManager()
{
    sdb.close();
}
