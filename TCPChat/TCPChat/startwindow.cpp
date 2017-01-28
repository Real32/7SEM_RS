#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtonContinue, SIGNAL(clicked()), this, SLOT(on_pushButtonContinue()));
    connect(ui->pushButtonLogin, SIGNAL(clicked()), this, SLOT(on_pushButtonLogin()));
    mclient = new MyClient();
    mclient->start("127.0.0.1", 1234);      // Set address and port to connect
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_pushButtonContinue()
{
    if (ui->lineEditRegLogin->text().isEmpty())
        (new QErrorMessage(this))->showMessage("Seems like a login os empty! Check it");
    else{
        ui->tabWidget->setCurrentIndex(1);
        mclient->setMessage("register");
        mclient->startTransfer();

        mclient->setMessage(ui->lineEditRegLogin->text());
        mclient->startTransfer();

        mclient->setMessage(ui->lineEditRegPassw->text());
        mclient->startTransfer();
    }
}

void StartWindow::on_pushButtonLogin()
{
    if (ui->lineEditLogLogin->text().isEmpty())
        (new QErrorMessage(this))->showMessage("Login or password are wrong! Check it");
    else{
        mclient->setMessage("login");
        mclient->startTransfer();

        mclient->setMessage(ui->lineEditLogLogin->text());
        mclient->startTransfer();

        mclient->setMessage(ui->lineEditLogPassw->text());
        mclient->startTransfer();


        mwindow = new MainWindow(this);
        mwindow ->setNickname(ui->lineEditLogLogin->text());
        close();
        mwindow->show();
    }
}
