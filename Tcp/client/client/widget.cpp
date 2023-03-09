#include "widget.h"
#include "ui_widget.h"
#include <iostream>
using namespace std;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建一个socket会话
    tcpSocket = new QTcpSocket(this);
}

void Widget::connected_Slot(){
    //触发有东西可读的信号，由readyRead_Slot()函数去处理
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead_Slot()));
}

//读取操作
void Widget::readyRead_Slot(){
    ui->receive_plainTextEdit->appendPlainText(tcpSocket->readAll());
}


Widget::~Widget()
{
    delete ui;
}


//打开客户端
void Widget::on_open_pushButton_clicked()
{
    //链接IP，设置端口号，端口号转成无符号类型
    tcpSocket->connectToHost(ui->ip_lineEdit->text(),ui->portnum_lineEdit->text().toUInt());
    //触发连接信号，由connected_Slot()去处理
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(connected_Slot()));
}

//关闭客户端
void Widget::on_close_pushButton_clicked()
{
    tcpSocket->close();
}

//发送数据
void Widget::on_send_pushButton_clicked()
{
    tcpSocket->write(ui->send_lineEdit->text().toLocal8Bit().data());
    //tcpSocket->close();
}

