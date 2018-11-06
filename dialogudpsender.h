#ifndef DIALOGUDPSENDER_H
#define DIALOGUDPSENDER_H

#include <QDialog>
#include <QLabel>
#include <QUdpSocket>
#include <QHostInfo>
namespace Ui {
class Dialogudpsender;
}

class Dialogudpsender : public QDialog
{
    Q_OBJECT

public:

    explicit Dialogudpsender(QWidget *parent = nullptr);
    ~Dialogudpsender();

private slots:
   // void onSocketStateChange(QAbstractSocket::SocketState socketState);
    void onSocketReadyRead();
    void on_btnSend_clicked();

    void on_btnBroadcast_clicked();

    void on_actStart_clicked();

    void on_actStop_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();


private:
    void on_actStart_triggered();
    void on_actStop_triggered();

    Ui::Dialogudpsender *ui;
    QLabel *LabSocketState;
    QUdpSocket *udpSocket;
    QString getLocalIP();//获取本机ip地址
};

#endif // DIALOGUDPSENDER_H
