#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H
#include <QAudioProbe>
#include <QAudioRecorder>
#include <QMediaRecorder>
#include <QObject>

class audiorecorder : public QObject
{
    Q_OBJECT
public:
    explicit audiorecorder(QObject *parent = 0);
    explicit audiorecorder(QString device,QObject *parent = 0);
    QAudioRecorder *player;
    void togglePlay();
    QAudioFormat getFormat();
signals:

public slots:

private:
QAudioFormat *format = 0;
};

#endif // AUDIORECORDER_H
