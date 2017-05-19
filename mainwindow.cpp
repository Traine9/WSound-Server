#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractSocket>
#include <QHostInfo>
#include <windows.h>
#include <QThread>
#include <QFileDialog>
static QVariant boxValue(const QComboBox *box)
{
    int idx = box->currentIndex();
    if (idx == -1)
        return QVariant();

    return box->itemData(idx);
}



QHostAddress localIP()
{
    QHostAddress locIP;
    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());

    if (!info.addresses().isEmpty()) {
        QList<QHostAddress> addr = info.addresses();
        locIP = addr.first();
        return locIP;
    }

}





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    ui->label->setText(QString(QHostAddress::LocalHost));
    //    QHostAddress d = QHostAddress::LocalHost;

    //start server
   // tcpthread = new QThread;

    server = new tcpserver;
    // server->moveToThread(tcpthread);
    //  tcpthread->start();
    connect(server,SIGNAL(listupdated()),this,SLOT(updatelist()));

    connect(server->server,SIGNAL(newConnection()),this,SLOT(newConnect()));
    //********


    //debug off
    ui->lineEditSend->setVisible(0);
    ui->pushButtonSend->setVisible(0);
    ui->pushButton->setVisible(0);
    ui->pushButton_2->setVisible(0);

    //show ip
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            if(address.toString().indexOf("192") != -1)
                ui->label->setText(address.toString());
    }
    //*****

    //QHostAddress d(localIP().toIPv4Address());

    //qDebug()<<d.toString();
    //d =QHostAddress(d.toIPv6Address());
    //qDebug()<<d.protocol();
    //qDebug()<<localIP().toString();
    //qDebug()<<QHostInfo::localDomainName();

    //qDebug()<<locIP.ConvertV4MappedToIPv4;
    recorder = new audiorecorder(boxValue(ui->combo_audio_devices).toString(),this);

    probe = new QAudioProbe;
    probe->
            connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)),
                    this, SLOT(processBuffer(QAudioBuffer)));
    probe->setSource(recorder->player);


    QStringList audioinputs = recorder->player->audioInputs();

    for(auto i = audioinputs.end() - 1;i >= audioinputs.begin();i--)
    {
        ui->combo_audio_devices->addItem(*i, QVariant(*i));
    }
    //recorder->togglePlay();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    // qDebug()<<server.peerAddress();
    // server->socket->peerAddress();

}

void MainWindow::on_pushButton_2_clicked()
{


    server->readData();
}

void MainWindow::on_pushButtonSend_clicked()
{
    QString str = ui->lineEditSend->text();
    QByteArray data;
    data.append(str);

    socket = new UDPSocket(server->socket->peerAddress(), 1234);
    qDebug()<<"send to "<<server->socketlist.first()->peerAddress()<<"    "<<data;
    for(int i =0;i<500;i++)
        socket->SendData(&data);
}

void MainWindow::updatelist()
{
    ui->listIp->clear();
    QStringList temp;
    QTcpSocket *temp2;
    foreach(temp2,server->socketlist)
    {
        temp.push_back(temp2->peerAddress().toString());
    }
    ui->listIp->addItems(temp);

}

void MainWindow::newConnect()
{
    qDebug()<<"newConnect";
  //recorder = new audiorecorder(boxValue(ui->combo_audio_devices).toString(),this);
//    if(format != 0)
//    {
////        QByteArray data(((char*)format));

////    server->socket->write(data);
////    format = 0;
////    format = (QAudioFormat*)data.data();
////            qDebug()<<"format sent"<<*format;
//       }

socket = new UDPSocket(server->socket->peerAddress(), 1234);
connect(this,SIGNAL(sendAll(QByteArray*)),socket,SLOT(SlotSendData(QByteArray*)));
updatelist();
}




void MainWindow::processBuffer(const QAudioBuffer &buffer)
{
    //qDebug()<<buffer.byteCount();
    //qDebug()<<buffer.data();
    // qDebug()<< buffer.format();

    if(socket != 0 )
    {

        QByteArray mydata;
        mydata.append(buffer.constData<char>(),buffer.byteCount());
        QAudioBuffer buffer2(mydata,recorder->getFormat());
        QByteArray mydata2;
        mydata2.append(buffer2.constData<char>(),buffer2.byteCount());
        //qDebug()<<"data sent "<<
        //socket->SendData(&mydata2);
        emit sendAll(&mydata2);
        static bool f = 1;
        if(f)
        {

            f=0;
            qDebug()<<buffer2.format();

        }
    }

    //qDebug()<<mydata.toHex();


}


void MainWindow::on_pushButton_play_clicked()
{
    //  QString fileName = QFileDialog::getSaveFileName();

    //recorder->player->setOutputLocation(QUrl::fromLocalFile(fileName));
   // Sleep(2000);

   //keybd_event(VK_MEDIA_PREV_TRACK, 0,0,0);
     //   keybd_event(VK_MEDIA_PREV_TRACK, 0,KEYEVENTF_KEYUP,0);

    recorder->player->setAudioInput(boxValue(ui->combo_audio_devices).toString());
    recorder->togglePlay();
}
