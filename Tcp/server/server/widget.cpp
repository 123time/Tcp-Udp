#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnection_Slot()));
}

void Widget::newConnection_Slot(){
    //创建一个socket会话
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead_Slot()));
}
//读取收到的数据
void Widget::readyRead_Slot(){
    QString buf;
    buf = tcpSocket->readAll();
    ui->receive_plainTextEdit->appendPlainText(buf);
}

Widget::~Widget()
{
    delete ui;
}

//打开开始监听
void Widget::on_open_pushButton_clicked()
{
    //开启监听，监听来自任何ip的连接，端口号转为无符号类型
    tcpServer->listen(QHostAddress::Any,ui->portnum_lineEdit->text().toUInt());
}

//tcp关闭服务器
void Widget::on_close_pushButton_clicked()
{
    tcpServer->close();
}

//tcp发送
void Widget::on_send_pushButton_clicked()
{
    tcpSocket->write(ui->send_lineEdit->text().toLocal8Bit().data());
}

