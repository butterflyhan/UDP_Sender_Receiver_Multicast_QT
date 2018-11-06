#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogupdmulticast.h"
#include "dialogudpsender.h"
#include "tcpserversocket.h"
#include "tcpclientsocket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    dialogupdmulticast udpmulticast;
    Dialogudpsender   udpsender;
    tcpserversocket   tcpserver;
    tcpclientsocket   tcpclient;
};

#endif // MAINWINDOW_H