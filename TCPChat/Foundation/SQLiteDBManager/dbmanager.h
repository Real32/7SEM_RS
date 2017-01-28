#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>
#include <QDebug>

class DBManager : public QObject
{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = 0);
    void createTableUser(QString username);

    void insertLogin(QString username, QString login);
    void insertPassword(QString username, QString password);
    void insertFriend(QString username, QString friendname);
    void insertInvitesIn(QString username, QString invitesIN);
    void insertInvitesOut(QString username, QString invitesOUT);

    QString getLogin(QString username);
    QString getPassword(QString username);
    QString getFriends(QString username);
    QString getInvitesIn(QString username);
    QString getInvitesOut(QString username);

    void updateFriend(QString username);
    void updateInviteIn(QString username);
    void updateInviteOut(QString username);

    ~DBManager();
signals:

public slots:

private:
    QSqlDatabase sdb;
    QSqlQuery *query;
};

#endif // DBMANAGER_H
