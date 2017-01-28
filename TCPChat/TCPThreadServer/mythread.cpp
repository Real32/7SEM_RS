#include "mythread.h"

MyThread::MyThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
    db = new DBManager();
    db->createTableMessages();
    db->getMessagesFromTo("user", "user2");
}

void MyThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void MyThread::parseMessage(QString message)
{



    QStringList parsedlist = message.split("\n");
    qDebug() << Q_FUNC_INFO << parsedlist.at(0);
    if(parsedlist.at(0) == "register"){
        db->createTableUser(parsedlist.at(1));
        db->insertLogin(parsedlist.at(1), parsedlist.at(1));
        db->insertPassword(parsedlist.at(1),parsedlist.at(2));
        socket->write("Ok\n");
        return;
    }else if(parsedlist.at(0) == "login"){
        if(db->getLogin(parsedlist.at(1))==parsedlist.at(1) && db->getPassword(parsedlist.at(1))==parsedlist.at(2))
            socket->write("Ok\n");
        else
            socket->write("Error\nAutification error. No such user");
            return;
    }else if(parsedlist.at(0) == "addFriend"){
        if(db->getAllTables().contains(parsedlist.at(2), Qt::CaseInsensitive)){
            socket->write("Ok\n");
            db->insertInvitesOut(parsedlist.at(1), parsedlist.at(2));
            db->insertInvitesIn(parsedlist.at(2), parsedlist.at(1));
            db->insertFriend((parsedlist.at(1)), parsedlist.at(2));
        }
        else{
            socket->write("Error\nCan't add new friend. No such user");
        }
        return;
    }else if(parsedlist.at(0) == "listFriends"){
            socket->write("Ok\n");
            QByteArray ba = db->getFriends(parsedlist.at(1)).toLatin1()+"\n";
            int size = ba.length();
            socket->write(ba.data(), size);
            return;
        }else if(parsedlist.at(0) == "sendMessage"){
        db->insertMessagesFromTo(parsedlist.at(1), parsedlist.at(2), parsedlist.at(3));

        socket->write("Ok\n");
        }else if(parsedlist.at(0) == "getNewMessages"){
        db->insertMessagesFromTo(parsedlist.at(1), parsedlist.at(2), parsedlist.at(3));
        QByteArray gm = db->getMessagesFromTo(parsedlist.at(1), parsedlist.at(2)).toLatin1() +"\n";
        socket->write("Ok\n");
        int size = gm.length();
        socket->write(gm.data(), size);
        return;
        }else{
            socket->write("Error\nCan't get message.");
        }
}

void MyThread::readyRead()
{
    // get the information
    QByteArray Data = socket->readAll();
    //db->insertLogin("user1", "login");
    parseMessage(Data.data());
    // will write on server side window
    qDebug() << socketDescriptor << " Data in: " << Data;
    //qDebug()<<db->getLogin("user1");
    socket->write(Data);
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";


    socket->deleteLater();
    exit(0);
}
