#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QStringList>
#include <QStringListModel>
#include <QWidget>
#include <QTimer>
#include "myclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void returnPressed();
    void setNickname(QString name);
private slots:
    void onFriendClicked();
    void onpushButtonSMessage();
    void onpushButtonCloseDialogClicked();
    void onpushButtonAddFriendClicked();
    void friendsList_upd();
private:
    QStringListModel *model;
    QStringList friendsList;
    Ui::MainWindow *ui;
    MyClient *mclient;
    QTimer *timer;
};

#endif // MAINWINDOW_H
