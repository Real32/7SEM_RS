#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QErrorMessage>
#include "mainwindow.h"
#include "myclient.h"

namespace Ui {
class StartWindow;
}

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = 0);
    ~StartWindow();
private slots:
    void on_pushButtonContinue();
    void on_pushButtonLogin();

private:
    MainWindow *mwindow;
    Ui::StartWindow *ui;
    MyClient *mclient;
};

#endif // STARTWINDOW_H
