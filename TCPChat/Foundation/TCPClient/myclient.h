#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QObject *parent = 0);
    ~MyClient();
    void start(QString address, quint16 port);
signals:

public slots:
  void startTransfer();
  void receiveMessage();
private:
  QTcpSocket socket;
};

#endif // MYCLIENT_H
