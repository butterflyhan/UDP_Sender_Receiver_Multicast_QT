#include "dialogupdmulticast.h"
#include "ui_dialogupdmulticast.h"

dialogupdmulticast::dialogupdmulticast(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogupdmulticast)
{
    ui->setupUi(this);
    LabSocketState=new QLabel("Socket状态: ");
    LabSocketState->setMidLineWidth(200);
    //ui->statusBar->addWidget(LabSocketState);
    QString localIP=getLocalIP();//本机ip
    this->setWindowTitle(this->windowTitle()+"----本机IP:"+localIP);
    ui->lineEdit_IP->setText("239.255.43.21");
    ui->lineEdit_bind->setText("22222");
    ui->actStop->setEnabled(false);
    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);


    udpSocket = new QUdpSocket(this);
    udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption,1);
  //  connect(udpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState socketState)),this,
  //          SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
  //  onSocketStateChange(udpSocket->state());
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));

}

dialogupdmulticast::~dialogupdmulticast()
{
    delete udpSocket;
    delete LabSocketState;

    delete ui;
}

QString dialogupdmulticast::getLocalIP()
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


void dialogupdmulticast::on_actStart_triggered()
{

     ui->textEdit->clear();
    //tcpClient->close();//取消现有连接
     QString IP =ui->lineEdit_IP->text();
     groupAddress=QHostAddress(IP);//多播组地址
     quint16 groupPort=ui->lineEdit_bind->text().toUShort();
    if(udpSocket->bind(QHostAddress::AnyIPv4,groupPort,QUdpSocket::ShareAddress))
    {
        udpSocket->joinMulticastGroup(groupAddress);
       ui->textEdit->append("**加入组播成功!");
       ui->textEdit->append("**组播地址IP:"+IP);
       ui->textEdit->append("**绑定端口:"
                            +QString::number(groupPort));
       ui->actStart->setEnabled(false);
       ui->actStop->setEnabled(true);
       ui->lineEdit_IP->setEnabled(false);
       ui->lineEdit_bind->setEnabled(false);
    }
    else
    {
        this->ui->textEdit->setText("**绑定端口失败\n");

    }
/*
    ui->textEdit->clear();
    QString IP=ui->lineEdit_IP->text();//获取ip地址
    quint16  port =ui->lineEdit_Port->text().toLongLong();
   // QHostAddress addr(IP);
   tcpClient->connectToHost(IP,port);
   ui->actStart->setEnabled(false);
   ui->actStop->setEnabled(true);
   */

}

void dialogupdmulticast::on_actStop_triggered()
{//解除绑定
    udpSocket->leaveMulticastGroup(groupAddress);//退出组播
    udpSocket->abort();//解除绑定
    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);
    ui->lineEdit_IP->setEnabled(true);
    ui->lineEdit_bind->setEnabled(true);
    ui->textEdit->append("**已退出组播，解除绑定端口!");
}


void dialogupdmulticast::on_btnSend_clicked()
{
    quint16 groupPort =ui->lineEdit_bind->text().toUShort();
    QString msg=ui->lineEdit->text();//发送消息
    QByteArray Datagram=msg.toUtf8();
    udpSocket->writeDatagram(Datagram,groupAddress,groupPort);
    ui->textEdit->append("[multicst:]"+msg);
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
}

void dialogupdmulticast::onSocketReadyRead()
{//读取收到的数据报

    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagpram;
        qint64 test=udpSocket->pendingDatagramSize();
        QString int64toqstinrg=QString::number(test);
        int stringtoint=int64toqstinrg.toInt();
        datagpram.resize(stringtoint);


      //  datagpram.resize(udpSocket->pendingDatagramSize());
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

/*
void dialogupdmulticast::onSocketStateChange(QAbstractSocket::SocketState socketState)
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

void dialogupdmulticast::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
}

void dialogupdmulticast::on_pushButton_4_clicked()
{
    this->close();
}

void dialogupdmulticast::on_actStop_clicked()
{
    on_actStop_triggered();

}

void dialogupdmulticast::on_actStart_clicked()
{

    on_actStart_triggered();
}
