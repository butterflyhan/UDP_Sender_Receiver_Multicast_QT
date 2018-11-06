#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
      udpsender.show();
       udpsender.exec();
       this->show();
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
     udpmulticast.show();
       udpmulticast.exec();
         this->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->hide();
     tcpserver.show();
       tcpserver.exec();
         this->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->hide();
    tcpclient.show();
    tcpclient.exec();
    this->show();
}
