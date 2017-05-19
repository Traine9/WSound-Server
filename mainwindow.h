#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QThread>
#include <QMainWindow>

#include "audiorecorder.h"
#include "tcpserver.h"
#include "udpsocket.h"
#include <QNetworkInterface>
#include <QAudioBuffer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButtonSend_clicked();
    void updatelist();
    void newConnect();
    void processBuffer(const QAudioBuffer&);
    void on_pushButton_play_clicked();

signals:
    sendAll(QByteArray*);

private:
    QThread *tcpthread = 0;
    //QAudioRecorder *player;
    Ui::MainWindow *ui;
    tcpserver *server;
    UDPSocket *socket;
    audiorecorder *recorder;
    QAudioProbe *probe;
     QAudioFormat *format;

};

#endif // MAINWINDOW_H
