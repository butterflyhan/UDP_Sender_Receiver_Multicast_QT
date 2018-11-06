#include "dialogudpsender.h"
#include "ui_dialogudpsender.h"

Dialogudpsender::Dialogudpsender(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogudpsender)
{
    ui->setupUi(this);

    LabSocketState=new QLabel("Socket状态: ");
    LabSocketState->setMidLineWidth(200);
    QString localIP=getLocalIP();//本机ip
    this->setWindowTitle(this->windowTitle()+"----本机IP:"+localIP);
    ui->lineEdit_IP->setText(localIP);
    ui->actStop->setEnabled(false);
    ui->lineEdit_Port->setText("5555");
    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);
    udpSocket = new QUdpSocket(this);
 //  connect(udpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState socketState)),this,
 //                           SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
 //   onSocketStateChange(udpSocket->state());
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));
}

Dialogudpsender::~Dialogudpsender()
{
    delete udpSocket;
    delete LabSocketState;
    delete ui;
}

QString Dialogudpsender::getLocalIP()
{
        QString hostName=QHostInfo::localHostName();//本地主机名
        QHostInfo hostInfo=QHostInfo::fromName(hostName);
        QString localIP="";
        QList<QHostAddress> addList=hostInfo.addresses();

        if(!addList.isEmpty())
        {
            for(int i=0;i<addList.count();i++)
            {
                QHostAddress aHost=addList.at(i);
                if(QAbstractSocket::IPv4Protocol==aHost.protocol())
                {
                    localIP=aHost.toString();
                    break;
                }
            }
        }
    return localIP;
}

/*
void Dialogudpsender::onSocketStateChange(QAbstractSocket::SocketState socketState)
{//socket 状态发生变化时
            switch (socketState) {
            case QAbstractSocket::UnconnectedState:
                LabSocketState->setText("socket状态:UnconnectedState");
                break;
            case QAbstractSocket::HostLookupState:
                LabSocketState->setText("socket状态:HostLookupState");
                break;
            case QAbstractSocket::ConnectingState:
                LabSocketState->setText("socket状态:ConnectingState");
                break;
            case QAbstractSocket::ConnectedState:
                LabSocketState->setText("socket状态:ConnectedState");
                break;
            case QAbstractSocket::BoundState:
                LabSocketState->setText("socket状态:BoundState");
                break;
            case QAbstractSocket::ClosingState:
                LabSocketState->setText("socket状态:ClosingState");
                break;
            case QAbstractSocket::ListeningState:
                LabSocketState->setText("socket状态:ListeningState");
                break;
    }

}

*/

void Dialogudpsender::on_actStart_triggered()
{
     ui->textEdit->clear();
     quint16 port=ui->lineEdit_bind->text().toUShort();
    if(udpSocket->bind(port))
    {
       ui->textEdit->append("**已成功绑定!");
       ui->textEdit->append("**绑定端口:"
                            +QString::number(udpSocket->localPort()));
       ui->actStart->setEnabled(false);
       ui->actStop->setEnabled(true);
    }
    else
    {
        this->ui->textEdit->setText("**绑定失败\n");

    }
}

void Dialogudpsender::on_actStop_triggered()
{//解除绑定
    udpSocket->abort();
    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);
    ui->textEdit->append("**已经解除绑定!");
}

void Dialogudpsender::onSocketReadyRead()
{//读取收到的数据报

    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagpram;

        qint64 test=udpSocket->pendingDatagramSize();
        QString int64toqstinrg=QString::number(test);
        int stringtoint=int64toqstinrg.toInt();
        datagpram.resize(stringtoint);
       // datagpram.resize(udpSocket->pendingDatagramSize());
        QHostAddress peerAddr;
        quint16 peerPort;
        udpSocket->readDatagram(datagpram.data(),datagpram.size(),&peerAddr,&peerPort);
        QString str=datagpram.data();
        QString peer="[From "+peerAddr.toString()+":"+QString::number(peerPort)+"]";
        ui->textEdit->append(peer+str);
    }
    /*
    QByteArray buffer;
    buffer = tcpClient->readAll();//读取数据缓存区
    if(!buffer.isEmpty())
    {
       // QString str = this->ui->textEdit->toPlainText();
       QString  str=tr(buffer);
        this->ui->textEdit->append("[in]:"+str);
    }
    */
}

void Dialogudpsender::on_btnSend_clicked()
{
    QString targetIP=ui->lineEdit_IP->text();
    QHostAddress targetAddr(targetIP);
    quint16 targetPort =ui->lineEdit_Port->text().toUShort();
    QString msg=ui->lineEdit->text();//发送消息
    QByteArray str=msg.toUtf8();
    udpSocket->writeDatagram(str,targetAddr,targetPort);
    ui->textEdit->append("[out:]"+msg);
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
}

void Dialogudpsender::on_btnBroadcast_clicked()
{// 广播消息按钮
    quint16 targetPort =ui->lineEdit_Port->text().toUShort();
    QString msg=ui->lineEdit->text();//发送消息
    QByteArray str=msg.toUtf8();
    udpSocket->writeDatagram(str,QHostAddress::Broadcast,targetPort);
    ui->textEdit->append("[out:]"+msg);
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();

}

void Dialogudpsender::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
}

void Dialogudpsender::on_pushButton_4_clicked()
{
    this->close();
}

void Dialogudpsender::on_actStop_clicked()
{
    on_actStop_triggered();

}

void Dialogudpsender::on_actStart_clicked()
{

    on_actStart_triggered();
}
