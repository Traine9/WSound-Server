#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QUdpSocket>
#include <QObject>
#include <QHostAddress>
//dich
class UDPSocket : public QObject
{
    Q_OBJECT

public:

   explicit UDPSocket(QHostAddress addr, uint16_t port, QObject *parent = 0);
    ~UDPSocket();
    int SendData(QByteArray *data);
    void read();
    QByteArray getData();

private slots:
    void readyRead();
    void SlotSendData(QByteArray *data);
private:
    QUdpSocket *socket;
    QHostAddress addr;
    uint16_t port;
    QByteArray buffer;
    int test;
};

#endif // UDPSOCKET_H
