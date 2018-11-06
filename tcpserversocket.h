#ifndef TCPSERVERSOCKET_H
#define TCPSERVERSOCKET_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
namespace Ui {
class tcpserversocket;
}

class tcpserversocket : public QDialog
{
    Q_OBJECT

public:

    explicit tcpserversocket(QWidget *parent = nullptr);
    ~tcpserversocket();

private  slots:
    void server_New_Connect();//服务器接收到客户端消息，连接槽函数
    void socket_Read_Data(); //服务器读客户端传输过来的数据
    void socket_Disconnect(); //服务器断开与客户端的槽函数
    void on_pushButton_Listen_clicked();
    void on_pushButton_Send_clicked();
    void on_pushButton_clear_clicked();
    void on_textEdit_Recive_textChanged();
    void on_textEdit_Send_textChanged();
    void on_pushButton_clicked();

private:

    Ui::tcpserversocket *ui;
    QTcpServer *server; //创建tcp的服务对象
    QTcpSocket *socket; //创建tcp的客户端对象
    QTcpSocket *m_tcpsocket;
     QList<QTcpSocket*> socket_list; //创建一个存放socket的list容器：

     QList<QString> ip_list;

     QString client_adress;
     QString getLocalIP();//获取本机ip地址

};

#endif // TCPSERVERSOCKET_H
