#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT
signals:
    void sendData(QString str);
private slots:
    void onButtonSend();
public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    MainWindow *mwindow;
    Ui::Login *ui;
};

#endif // LOGIN_H
