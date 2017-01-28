#include "myclient.h"

MyClient::MyClient(QObject *parent) : QObject(parent)
{
    connect(&socket, SIGNAL(connected()), this, SLOT(startTransfer()));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
}

MyClient::~MyClient()
{
    socket.close();
}

void MyClient::start(QString address, quint16 port)
{
    QHostAddress addr(address);
    socket.connectToHost(addr, port);
}

void MyClient::setMessage(QString mess)
{
    message = mess;
}

void MyClient::setRecMessage(QString mess)
{
    rmessage = mess;
}

void MyClient::setFriends(QString frie)
{
    friends = frie;
}

bool MyClient::recieveFlag()
{
    return flagOkError;
}

void MyClient::startTransfer()
{
    QByteArray ba = message.toLatin1()+"\n";
    int size = ba.length();
    socket.write(ba.data(), size);
    qDebug()<< Q_FUNC_INFO <<"message " << message << " transfered";
}

void MyClient::receiveMessage()
{
    // get the information
    QByteArray Data = socket.readAll();
    // will write on server side window
    qDebug() << " Recieved Message: " << Data;
    QString data = Data.data();
    QStringList parsedlist = data.split("\n");
    qDebug() << Q_FUNC_INFO << parsedlist.at(0);
        if(parsedlist.at(0)=="Ok" && parsedlist.at(1) == "addFriend"){
            flagOkError = 1;
            return;
        }else if(parsedlist.at(0)=="Ok" && parsedlist.at(2) == "listFriends"){
            setFriends(parsedlist.at(1));
            flagOkError = 1;
        }else if(parsedlist.at(0)=="Ok" && parsedlist.at(1) == "sendMessage"){
            setRecMessage(parsedlist.at(2) + " > " + parsedlist.at(3) + parsedlist.at(4));
        }
}
