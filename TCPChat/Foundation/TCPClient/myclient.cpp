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

void MyClient::startTransfer()
{
    socket.write("Hello, world/r/n", 16);
    qDebug()<<Q_FUNC_INFO<<"message trn";
}

void MyClient::receiveMessage()
{
    // get the information
    QByteArray Data = socket.readAll();

    // will write on server side window
    qDebug() << " Recieved Message: " << Data;

}
