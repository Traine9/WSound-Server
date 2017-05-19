#include "udpsocket.h"



UDPSocket::UDPSocket(QHostAddress addr, uint16_t port, QObject *parent)
    : QObject(parent)
{
    this->addr = addr;
    this->port = port;
    socket = new QUdpSocket;
    socket->bind( port);
}

UDPSocket::~UDPSocket()
{
    socket->close();
}

int UDPSocket::SendData(QByteArray *data)
{

    return  socket->writeDatagram(*data,addr,port);;

}

void UDPSocket::read()
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

QByteArray UDPSocket::getData()
{
    return buffer;
}

void UDPSocket::readyRead()
{
    buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(buffer.data(), buffer.size());
}

void UDPSocket::SlotSendData(QByteArray *data)
{
    SendData(data);
}
