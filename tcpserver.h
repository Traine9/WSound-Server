#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QTcpSocket>
#include <QObject>
#include <QTcpServer>
#include <QList>
#include <QThread>
class tcpserver : public QObject
{
    Q_OBJECT
public:
    explicit tcpserver(QObject *parent = 0);
    QList<QTcpSocket*> socketlist;
    QTcpSocket *socket;
    QTcpServer *server;

    void run();
    ~tcpserver();
signals:
    listupdated();
public slots:
    Disconnect();
    newConnection();
    readData();

};

#endif // TCPSOCKET_H
