#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class tcpclientsocket;
}

class tcpclientsocket : public QDialog
{
    Q_OBJECT

public:
    explicit tcpclientsocket(QWidget *parent = nullptr);
    ~tcpclientsocket();

private slots:
    void on_pushButton_Conncet_clicked();

    void on_pushButton_Send_clicked();

    void socket_Read_Data();
    void socket_Disconnected();

    void on_pushButton_clicked();

    void on_textEdit_Receive_textChanged();

    void on_textEdit_Send_textChanged();

    void on_pushButton_2_clicked();

private:
    Ui::tcpclientsocket *ui;
    QTcpSocket *socket;

};

#endif // TCPCLIENTSOCKET_H
