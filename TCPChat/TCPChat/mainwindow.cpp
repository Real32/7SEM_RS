#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStringListModel(this);     // Create model
    ui->listViewFriends->setModel(model);

    mclient = new MyClient();
    mclient->start("127.0.0.1", 1234);      // Set address and port to connect

    timer = new QTimer();
    timer->setInterval(3000); // set interval
    connect(timer, SIGNAL(timeout()), this, SLOT(friendsList_upd()));

    timer->start(); // start timers
    connect(ui->lineEditMessage, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(ui->listViewFriends, SIGNAL(clicked(QModelIndex)), this, SLOT(onFriendClicked()));
    connect(ui->pushButtonSMessage, SIGNAL(clicked()), this, SLOT(onpushButtonSMessage()));
    connect(ui->pushButtonCloseDialog, SIGNAL(clicked()), this, SLOT(onpushButtonCloseDialogClicked()));
    connect(ui->pushButtonAddFriend, SIGNAL(clicked()), this, SLOT(onpushButtonAddFriendClicked()));

//    friendsList << "user" ;    //test
//    friendsList << "user2" ;    //test
    model->setStringList(friendsList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::returnPressed()
{
    qDebug()<<Q_FUNC_INFO<<"return pressed";
    mclient->setMessage("sendMessage");
    mclient->startTransfer();
    mclient->setMessage(ui->labelNickname->text()); // FROM
    mclient->startTransfer();
    mclient->setMessage(ui->listViewFriends->currentIndex().data().toString()); // TO
    mclient->startTransfer();
    mclient->setMessage(ui->lineEditMessage->text()); // MESSAGE
    mclient->startTransfer();


    ui->textEdit->append(mclient->rmessage);
}

void MainWindow::setNickname(QString name)
{
    ui->labelNickname->setText(name);
}

void MainWindow::onFriendClicked()
{
    if(!ui->listViewFriends->currentIndex().isValid())
        return;
    ui->lineEditMessage->setEnabled(1);
    ui->pushButtonDelFriend->setEnabled(1);
    ui->pushButtonSMessage->setEnabled(1);

}

void MainWindow::onpushButtonSMessage()
{   /*create a new tab */
    QTextEdit *messageField = new QTextEdit;
    messageField->setReadOnly(1);
    ui->tabWidget->insertTab(ui->tabWidget->currentIndex()+1, messageField, ui->listViewFriends->currentIndex().data().toString());
}

void MainWindow::onpushButtonCloseDialogClicked()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}

void MainWindow::onpushButtonAddFriendClicked()
{
    mclient->setMessage("addFriend");
    mclient->startTransfer();

    mclient->setMessage(ui->labelNickname->text());
    mclient->startTransfer();

    mclient->setMessage(ui->lineEditAddFriend->text());
    mclient->startTransfer();
}

void MainWindow::friendsList_upd()
{
    QModelIndex index = ui->listViewFriends->currentIndex();

    qDebug()<<"get list friends";
    mclient->setMessage("listFriends");
    mclient->startTransfer();
    mclient->setMessage(ui->labelNickname->text());
    mclient->startTransfer();

    if(mclient->recieveFlag()){
        friendsList.clear();
        model->setStringList(friendsList);
        friendsList << mclient->friends ;    //test
        qDebug() << "wqfwfwf" << mclient->friends;
        model->setStringList(friendsList);
        ui->listViewFriends->setCurrentIndex(index);
    }
    qDebug()<<Q_FUNC_INFO<<"return pressed";
    mclient->setMessage("getMessages");
    mclient->startTransfer();
    mclient->setMessage(ui->labelNickname->text()); // FROM
    mclient->startTransfer();
    mclient->setMessage(ui->listViewFriends->currentIndex().data().toString()); // TO
    mclient->startTransfer();
}
