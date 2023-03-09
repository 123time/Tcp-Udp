#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QString>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QUdpSocket *udpSocket;

private slots:
    void on_open_pushButton_clicked();
    void readyRead_Slot();
    void on_send_pushButton_clicked();
    void on_close_pushButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
