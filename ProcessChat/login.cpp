#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->pushButton_accept, SIGNAL(clicked()), this, SLOT(onButtonSend()));
}

void Login::onButtonSend()
{
    mwindow = new MainWindow(this);
    if (!ui->lineEdit_nick->text().isEmpty())
        mwindow->recieveData(ui->lineEdit_nick->text());
    close();
    mwindow->show();
}

Login::~Login()
{
    qDebug() << Q_FUNC_INFO;
    delete ui;
}
