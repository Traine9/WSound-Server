#include "tcpserver.h"
#include <QThread>
//#define WINVER 0x0500
#include <Windows.h>

tcpserver::tcpserver(QObject *parent) : QObject(parent)
{





    server = new QTcpServer;
    socket = new QTcpSocket;




    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

    if(server->listen(QHostAddress::Any,55025))qDebug()<<"\nConnected\n";

    //server->waitForNewConnection(10000);
    //qDebug()<<"\ncntcrfsfd\n";
}

tcpserver::~tcpserver()
{
    socket->close();
}

tcpserver::Disconnect()
{

QTcpSocket *dsocket = (QTcpSocket*)QObject::sender();
qDebug()<<dsocket->peerAddress();
qDebug()<<"disconnected";
socketlist.removeAt(socketlist.indexOf(dsocket));
dsocket->close();
emit listupdated();


}

tcpserver::newConnection()
{
    qDebug()<<"\nfuck yeah\n";
    int i=1;

    socket = server->nextPendingConnection();



    connect(socket,SIGNAL(disconnected()),this,SLOT(Disconnect()));
    connect(socket,SIGNAL(channelReadyRead(int)),this,SLOT(readData()));
    //foreach (QTcpSocket* temp, socketlist) {
    //    if(temp-> == socket)
    //    {
    //        i=0;
    //    }

    //}

    socketlist.push_back(socket);


    qDebug()<<socket->peerAddress();
    readData();
    return 0;
}

tcpserver::readData()
{

    if(socket->state() == 3)
    {
        //socket->waitForBytesWritten();
        //socket->waitForReadyRead();
        auto temp = socket->readAll();
        if(temp != 0)
            qDebug()<<temp;
        {

        char c = temp.data()[0];
        switch (c) {
        case '1':

            keybd_event(VK_MEDIA_PREV_TRACK, 0,0,0);
            keybd_event(VK_MEDIA_PREV_TRACK, 0,KEYEVENTF_KEYUP,0);
           // qDebug()<<"prev";
            break;

        case '2':

            keybd_event(VK_MEDIA_NEXT_TRACK, 0,0,0);
            keybd_event(VK_MEDIA_NEXT_TRACK, 0,KEYEVENTF_KEYUP,0);
            break;

        case '3':

            keybd_event(VK_MEDIA_PLAY_PAUSE, 0,0,0);
            keybd_event(VK_MEDIA_PLAY_PAUSE, 0,KEYEVENTF_KEYUP,0);
            break;

        case '4':

            keybd_event(VK_VOLUME_MUTE, 0,0,0);
            keybd_event(VK_VOLUME_MUTE, 0,KEYEVENTF_KEYUP,0);
            break;
        case '5':

            keybd_event(VK_VOLUME_UP, 0,0,0);
            keybd_event(VK_VOLUME_UP, 0,KEYEVENTF_KEYUP,0);
            break;
        case '6':

            keybd_event(VK_VOLUME_DOWN, 0,0,0);
            keybd_event(VK_VOLUME_DOWN,0,KEYEVENTF_KEYUP,0);
            break;

        }
    }
    }
}
