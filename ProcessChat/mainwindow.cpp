#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ipc  = new IPCClass();
    tmr = new QTimer(this);
    ui->setupUi(this);

    model = new QStringListModel(this);     // Create model
    ui->listView->setModel(model);
    //qDebug()<<getpid();
    ipc->shmemory_create();
    ipc->msgQueu_create();
//    ipc->close_SHM();
//    ipc->close_msg();
    tmr->setInterval(1000); // set interval
    connect(tmr, SIGNAL(timeout()), this, SLOT(userList_upd()));

    tmr->start(); // start timers
    connect(ui->lineEdit_message, SIGNAL(returnPressed()), this, SLOT(returnPressed()));


}

void MainWindow::recieveData(QString str)
{
    ipc->write_toSHM();
    ipc->read_fromSHM();
    userIndex = ipc->get_clindex() - 1; // because because
    qDebug()<<"Index "<<userIndex;
    ui->label_nickname->setText(str + " pid: " + QString::number(getpid())); // recieve from shm
//    usersList << "<you> " + str;
    for(int i = 0; i < CLCOUNT; i++)
    {
        if(ipc->get_SHMpid(i)!=0)
        {
            usersList << QString::number(ipc->get_SHMpid(i)); // write QString(ipc->get_SHMpid(i)) to have fun
        }
    }
    model->setStringList(usersList);
    userCount = ipc->get_clcount();
}

void MainWindow::returnPressed()
{
    QString text = ui->lineEdit_message->text();
    if (text.isEmpty())
        return;
    if(!ui->listView->currentIndex().isValid())
        return;
    int Spid = ui->listView->model()->data(ui->listView->currentIndex()).toInt();
    QString message = "<" + ui->label_nickname->text() + "> " +  ui->lineEdit_message->text();
    QString nicknameS = ui->label_nickname->text() + ": ";
    qDebug() << Q_FUNC_INFO << Spid << ui->lineEdit_message->text();
    ipc->msg_send(Spid, nicknameS, ui->lineEdit_message->text());
    ui->textEdit->append(message);
    ui->lineEdit_message->clear();
}

void MainWindow::userList_upd()
{
    //qDebug()<<userCount<<" "<<ipc->get_clcount();
    QString mess = ipc->msg_recieveMessage();
    if(userCount!=ipc->get_clcount())
    {
            ipc->read_fromSHM();
            usersList.clear();
            for(int i = 0; i < CLCOUNT; i++)
            {
                if(ipc->get_SHMpid(i)!=0)
                {
                    usersList << QString::number(ipc->get_SHMpid(i)); // write QString(ipc->get_SHMpid(i)) to have fun
                }
            }
            //usersList << QString::number(ipc->get_SHMpid(userCount));
            userCount = ipc->get_clcount();
    }
    QModelIndex index = ui->listView->currentIndex();
    model->setStringList(usersList);
    ui->listView->setCurrentIndex(index);
    if(!mess.isEmpty())
    {
        ui->textEdit->append(mess);
    }
}

MainWindow::~MainWindow()
{
    qDebug() << Q_FUNC_INFO;
    ipc->set_clcount(ipc->get_clcount()-1);
    ipc->set_SHMpid(userIndex, 0);
    ipc->~IPCClass();
    if(ipc->get_clcount()==0)
    {
        ipc->close_SHM();
        ipc->close_msg();
        ipc->close_sem();
    }
    delete ui;
}
