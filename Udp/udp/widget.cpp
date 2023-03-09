#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);
}


Widget::~Widget()
{
    delete ui;
}


void Widget::readyRead_Slot(){
    //这个函数如果没有读取完就会返回true
    while(udpSocket->hasPendingDatagrams()){
        QByteArray array;
        //创建数组并且调整数组大小与数据一致
        array.resize(udpSocket->pendingDatagramSize());
        //udp没有readAll
        udpSocket->readDatagram(array.data(),array.size());

        QString buf;
        buf = array.data();
        ui->receive_plainTextEdit->appendPlainText(buf);

    }
}


void Widget::on_open_pushButton_clicked()
{
    if(udpSocket->bind(ui->localPort_lineEdit->text().toUInt()) == true){
        QMessageBox::information(this,"连接提示","连接成功！！");
        connect(udpSocket,SIGNAL(readyRead()),this,SLOT(readyRead_Slot()));
    }else {
       QMessageBox::critical(this,"连接提示","连接失败！！");
    }
}


void Widget::on_send_pushButton_clicked()
{
    quint16 port;
    QString sendbuf;

    QHostAddress address;
    //把目标ip转成QHostAddress类型
    address.setAddress(ui->aimIp_lineEdit->text());

    sendbuf = ui->send_lineEdit->text();

    port = ui->aimPort_lineEdit->text().toUInt();

    udpSocket->writeDatagram(sendbuf.toLocal8Bit().data(),sendbuf.length(),address,port);
}


void Widget::on_close_pushButton_clicked()
{
    udpSocket->close();
}

