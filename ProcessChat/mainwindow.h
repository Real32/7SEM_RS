#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QStringListModel>
#include <QTimer>
#include <ipcclass.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void recieveData(QString str);
    void returnPressed();
    void userList_upd();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    IPCClass *ipc;
    QStringListModel *model;
    QStringList usersList;
    QTimer *tmr;
    Ui::MainWindow *ui;
    int userCount;
    int userIndex;
};

#endif // MAINWINDOW_H
