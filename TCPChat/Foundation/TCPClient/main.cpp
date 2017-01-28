#include <QCoreApplication>
#include <myclient.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyClient client;
    client.start("127.0.0.1", 1234);
    return a.exec();
}
