#include "tcpclientsocket.h"
#include "ui_tcpclientsocket.h"

tcpclientsocket::tcpclientsocket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tcpclientsocket)
{
    ui->setupUi(this);

    this->ui->pushButton_Send->setEnabled(false);
    this->ui->lineEdit_IP->setText("192.168.31.123");
    this->ui->lineEdit_Port->setText("5555");
    socket = new QTcpSocket();
    QObject::connect(socket,&QTcpSocket::readyRead,this,&tcpclientsocket::socket_Read_Data);
    QObject::connect(socket,&QTcpSocket::disconnected,this,&tcpclientsocket::socket_Disconnected);


}

tcpclientsocket::~tcpclientsocket()
{
    delete this->socket;//删除客户端对象

    delete ui;
}

void tcpclientsocket::on_pushButton_Conncet_clicked()
{
    if(this->ui->pushButton_Conncet->text() == tr("连接"))
    {
        socket->abort();//取消现有连接
        socket->connectToHost(this->ui->lineEdit_IP->text(),this->ui->lineEdit_Port->text().toUShort());


        if(!socket->waitForConnected(300))
        {
            //qDebug()<<"连接服务器失败，请重新操作！";
            this->ui->textEdit_Receive->setText("连接服务器失败，请重新操作！\n");
            return;
        }
        else
        {
            this->ui->textEdit_Receive->setText("连接服务器成功！\n");
           // qDebug()<<"连接服务器成功！";

        }
        //发送按键使能
        this->ui->pushButton_Send->setEnabled(true);
        ui->pushButton_Conncet->setText("断开连接");

    }
    else
    {
        socket->disconnectFromHost();
        this->ui->pushButton_Conncet->setText("连接");
        this->ui->pushButton_Send->setEnabled(false);
    }
}

void tcpclientsocket::on_pushButton_Send_clicked()
{
    //qDebug()<<"Send:"<<this->ui->textEdit_Send->toPlainText();
    socket->write(this->ui->textEdit_Send->toPlainText().toUtf8());
    socket->flush();
}

//读取缓存区槽函数
void tcpclientsocket::socket_Read_Data()
{
    QByteArray buffer;
    buffer =socket->readAll();

    if(!buffer.isEmpty())
    {
        QString str = this->ui->textEdit_Receive->toPlainText();
        str+=tr(buffer);
        this->ui->textEdit_Receive->setText(str+"\n");
    }

}

void tcpclientsocket::socket_Disconnected()
{
    ui->pushButton_Send->setEnabled(false);
    ui->pushButton_Conncet->setText("连接");
    //qDebug()<<"断开连接";
    this->ui->textEdit_Receive->setText("断开连接");
}

void tcpclientsocket::on_pushButton_clicked()
{
    this->ui->textEdit_Receive->clear();
    this->ui->textEdit_Send->clear();
}

void tcpclientsocket::on_textEdit_Receive_textChanged()
{
    this->ui->textEdit_Receive->moveCursor(QTextCursor::End);
}

void tcpclientsocket::on_textEdit_Send_textChanged()
{
    this->ui->textEdit_Send->moveCursor(QTextCursor::End);
}

void tcpclientsocket::on_pushButton_2_clicked()
{
    this->close();
}
