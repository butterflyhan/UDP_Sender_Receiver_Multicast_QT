#include "tcpserversocket.h"
#include "ui_tcpserversocket.h"
//#include <QDebug>
#include <QMessageBox>
#include <QList>
#include <QHostInfo>
#include <QShortcut>
#include <QHostAddress>
tcpserversocket::tcpserversocket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tcpserversocket)
{
    ui->setupUi(this);
    server = new QTcpServer();//初始化QTcpserver对象


    QString localIP=getLocalIP();//本机ip


    this->ui->lineEdit_IP->setText(localIP);

    connect(server,&QTcpServer::newConnection,this,&tcpserversocket::server_New_Connect);
    this->ui->lineEdit_Port->setText("5555");
    this->ui->pushButton_Send->setEnabled(false);



}

tcpserversocket::~tcpserversocket()
{
    server->close();
    server->deleteLater();

    delete ui;
}

void tcpserversocket::on_pushButton_Listen_clicked()
{
     if(this->ui->pushButton_Listen->text() == tr("侦听"))
    {
         quint16 port=this->ui->lineEdit_Port->text().toUShort();
         if(server->listen(QHostAddress::Any,port))
        {
            this->ui->pushButton_Listen->setText("停止");
            this->ui->pushButton_Send->setEnabled(true);
            this->ui->textEdit_Recive->setText("监听成功\n");
        }
    }
    else if(this->ui->pushButton_Listen->text()==tr("停止"))
    {
      server->close();
        this->ui->pushButton_Listen->setText("侦听");
        this->ui->pushButton_Send->setEnabled(false);
     }

}

QString tcpserversocket::getLocalIP()
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


void tcpserversocket::on_pushButton_Send_clicked()
{
    for(int i = 0; i < socket_list.length(); i++)
        {
            QTcpSocket *item = socket_list.at(i);
            QString MESSAGE = this->ui->textEdit_Send->toPlainText().toUtf8();
          item->write(this->ui->textEdit_Send->toPlainText().toUtf8());
          item->flush();
        }
}

void tcpserversocket::server_New_Connect()
{
    QString IP;

    m_tcpsocket = server->nextPendingConnection();
    socket_list.append(m_tcpsocket);

    IP = m_tcpsocket->peerAddress().toString();
    IP.replace(QString("::ffff:"), QString(""));
    ip_list.append(IP);

    QObject::connect(m_tcpsocket,&QTcpSocket::readyRead,this,&tcpserversocket::socket_Read_Data);
    QObject::connect(m_tcpsocket,&QTcpSocket::disconnected,this,&tcpserversocket::socket_Disconnect);
    this->ui->pushButton_Send->setEnabled(true);
    ui->textEdit_IP->clear();
   for(int i = 0; i<ip_list.length();i++)
   {
     ui->textEdit_IP->append(ip_list.at(i));
   }

    this->ui->textEdit_Recive->setText("一个客户端连接成功!\n");
}

void tcpserversocket::socket_Read_Data()
{
    QByteArray message;
    for(int i = 0;i < socket_list.length();i ++)
    {
        message = socket_list.at(i)->readAll() ;
        if(!message.isEmpty())
        {
            QString str = this->ui->textEdit_Recive->toPlainText();
            str+=tr(message);
            this->ui->textEdit_Recive->setText(str+"\n");


            for(int i = 0; i < socket_list.length(); i++)
                {
                    QTcpSocket *item = socket_list.at(i);
                    item->write(message.data());
                    item->flush();

                }

        }

    }
}

void tcpserversocket::socket_Disconnect()
{
    for(int i = 0; i<socket_list.length();i++)
    {
        if(socket_list.at(i)->state()==QAbstractSocket::UnconnectedState)
        {
            socket_list.at(i)->close();
            socket_list.removeAt(i);
            ip_list.removeAt(i);

        }

        ui->textEdit_IP->clear();
       for(int i = 0; i<ip_list.length();i++)
       {
        ui->textEdit_IP->append(ip_list.at(i));
       }


    }
    ui->pushButton_Send->setEnabled(false);
    ui->textEdit_Recive->setText("连接中断\n");
}

void tcpserversocket::on_pushButton_clear_clicked()
{
    this->ui->textEdit_Recive->clear();
    this->ui->textEdit_Send->clear();
}

void tcpserversocket::on_textEdit_Recive_textChanged()
{
    this->ui->textEdit_Recive->moveCursor(QTextCursor::End);
}

void tcpserversocket::on_textEdit_Send_textChanged()
{
    this->ui->textEdit_Send->moveCursor(QTextCursor::End);
}


void tcpserversocket::on_pushButton_clicked()
{
    server->close();

    this->close();
}
