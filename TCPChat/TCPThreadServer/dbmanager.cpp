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
           //query=new QSqlQuery(sdb);
    }
}

void DBManager::createTableUser(QString username)
{
    QSqlQuery query;
    QString str = "CREATE TABLE " + username +" ("
            "login VARCHAR(50), "
            "password VARCHAR(50), "
            "friends VARCHAR(50), "
            "invitesin VARCHAR(50), "
            "invitesout VARCHAR(50)"
            ")";
    qDebug() << str;
    bool result = query.exec(str);
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't CREATE TABLE USERS";
    }

}

void DBManager::createTableMessages()
{
    QSqlQuery query;
    QString str = "CREATE TABLE messages ("
            "userfrom VARCHAR(50), "
            "userto VARCHAR(50), "
            "message VARCHAR(250)"
            ")";
    qDebug() << str;
    bool result = query.exec(str);
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't CREATE TABLE MESSAGES";
    }

}

void DBManager::insertLogin(QString username, QString login)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + username + " (login) "
                  "VALUES (:login)");
    query.bindValue(":login", login);

    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't INSERT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "INSERT LOGIN SUCCESS";
    }
}

void DBManager::insertPassword(QString username, QString password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + username + " (password) "
                  "VALUES (:password)");
    query.bindValue(":password", password);

    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't INSERT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "INSERT PASSWORD SUCCESS";
    }
}

void DBManager::insertFriend(QString username, QString friendname)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + username + " (friends) "
                  "VALUES (:friend)");
    query.bindValue(":friend", friendname);

    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't INSERT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "INSERT FRIEND SUCCESS";
    }
}

void DBManager::insertInvitesIn(QString username, QString invitesIN)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + username + " (invitesin) "
                  "VALUES (:friend)");
    query.bindValue(":invitesin", invitesIN);

    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't INSERT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "INSERT INVITESIN SUCCESS";
    }
}

void DBManager::insertInvitesOut(QString username, QString invitesOUT)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + username + " (invitesout) "
                  "VALUES (:invitesout)");
    query.bindValue(":invitesin", invitesOUT);

    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't INSERT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "INSERT INVITESOUT SUCCESS";
    }
}

void DBManager::insertMessagesFromTo(QString usernameFrom, QString usernameTo, QString message)
{
    QSqlQuery query;
    query.prepare("INSERT INTO messages (userfrom, userto, message) "
                  "VALUES (:userfrom, :userto, :message)");
    query.bindValue(":userfrom", usernameFrom);
    query.bindValue(":userto", usernameTo);
    query.bindValue(":message", message);
    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't INSERT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "INSERT MESSAGE SUCCESS";
    }
}

QString DBManager::getLogin(QString username)
{
    QSqlQuery query;
    QString login;
    query.prepare("SELECT login FROM " + username);
    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT LOGIN SUCCESS";
    }
    while (query.next()) {
        login = login + query.value(0).toString();
    }
    return login;
}

QString DBManager::getPassword(QString username)
{
    QSqlQuery query;
    QString password;
    query.prepare("SELECT password FROM " + username);
    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT PASSWORD SUCCESS";
    }
    while (query.next()) {
        password = password + query.value(0).toString();
    }
    return password;
}

QString DBManager::getFriends(QString username)
{
    QSqlQuery query;
    QString friends;
    query.prepare("SELECT friends FROM " + username);
    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT FRIEND SUCCESS";
    }
    while (query.next()) {
        friends = friends + query.value(0).toString();
    }
    return friends;
}

QString DBManager::getInvitesIn(QString username)
{
    QSqlQuery query;
    QString invitesin;
    query.prepare("SELECT invitesin FROM " + username);
    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT INVITESIN SUCCESS";
    }
    while (query.next()) {
        invitesin = invitesin + query.value(0).toString();
    }
    return invitesin;
}

QString DBManager::getInvitesOut(QString username)
{
    QSqlQuery query;
    QString invitesout;
    query.prepare("SELECT invitesout FROM " + username);
    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT INVITESOUT SUCCESS";
    }
    while (query.next()) {
        invitesout = invitesout + query.value(0).toString();
    }
    return invitesout;
}

QString DBManager::getAllTables()
{
    QSqlQuery query;
    QString tables;
    query.prepare("SELECT name FROM sqlite_master WHERE type = 'table'");
    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT TABLENAMES SUCCESS";
    }
    while (query.next()) {
        tables = tables + query.value(0).toString();
    }
    return tables;
}

QString DBManager::getMessagesFromTo(QString usernameFrom, QString usernameTo)
{
    QSqlQuery query;
    QString message1;
    query.prepare("SELECT message FROM messages WHERE userfrom = " + usernameFrom +" AND userto = " + usernameTo);
    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't SELECT";
        }
    else{
        qDebug() << Q_FUNC_INFO << "SELECT TABLENAMES SUCCESS";
    }
    while (query.next()) {
        message1 = message1 + query.value(0).toString();
    }
    return message1;
}

void DBManager::updateFriend(QString username)
{
    QSqlQuery query;
    query.prepare("UPDATE " + username + " SET friends = NULL");
    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't UPDATE";
        }
    else{
        qDebug() << Q_FUNC_INFO << "UPDATE FRIENDS SUCCESS";
    }
}

void DBManager::updateInviteIn(QString username)
{
    QSqlQuery query;
    query.prepare("UPDATE " + username + " SET invitesin = NULL");
    bool result = query.exec();
    if (!result) {
        qDebug() << Q_FUNC_INFO << "Can't UPDATE";
        }
    else{
        qDebug() << Q_FUNC_INFO << "UPDATE INVITESIN SUCCESS";
    }
}

void DBManager::updateInviteOut(QString username)
{
    QSqlQuery query;
    query.prepare("UPDATE " + username + " SET invitesout = NULL");
    bool result = query.exec();
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
