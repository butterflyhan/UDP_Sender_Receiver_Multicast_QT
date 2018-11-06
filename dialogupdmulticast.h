#ifndef DIALOGUPDMULTICAST_H
#define DIALOGUPDMULTICAST_H

#include <QDialog>
#include <QLabel>
#include <QUdpSocket>
#include <QHostAddress>
#include <QHostInfo>
namespace Ui {
class dialogupdmulticast;
}

class dialogupdmulticast : public QDialog
{
    Q_OBJECT

public:

    explicit dialogupdmulticast(QWidget *parent = nullptr);
    ~dialogupdmulticast();

private slots:
   // void onSocketStateChange(QAbstractSocket::SocketState socketState);
    void onSocketReadyRead();

    void on_btnSend_clicked();

    void on_actStart_clicked();

    void on_actStop_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
private:
    void on_actStart_triggered();
    void on_actStop_triggered();


    Ui::dialogupdmulticast *ui;
    QLabel *LabSocketState;
    QUdpSocket *udpSocket;
    QHostAddress groupAddress;//记录组播地址
    QString getLocalIP();//获取本机ip地址
};

#endif // DIALOGUPDMULTICAST_H
