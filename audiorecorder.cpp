#include "audiorecorder.h"

audiorecorder::audiorecorder(QObject *parent) : QObject(parent)
{
    player = new QAudioRecorder;
//    QStringList audioinputs = player->audioInputs();

//    for(auto i = audioinputs.end() - 1;i >= audioinputs.begin();i--)
//    {
//        ui->combo_audio_devices->addItem(*i, QVariant(*i));
//    }


}

audiorecorder::audiorecorder(QString device, QObject *parent) : QObject(parent)

{
    player = new QAudioRecorder;
    player->setAudioInput(device);


    //audio codecs
   QString codec = player->supportedAudioCodecs().first();
   int sampleRate = player->supportedAudioSampleRates().last();
  sampleRate = 48000;
   int channels = 2;
   int bitrate = 1000000;
 QString container = player->supportedContainers().last();
 qDebug()<<"codec "<<codec<<" rate "<<sampleRate<<" container "<<container;

    QAudioEncoderSettings settings;
    settings.setCodec(codec);
    settings.setSampleRate(sampleRate);
    settings.setBitRate(bitrate);
    settings.setChannelCount(channels);
    settings.setQuality(QMultimedia::VeryHighQuality);
    //settings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
     settings.setEncodingMode(QMultimedia::AverageBitRateEncoding);
    format = new QAudioFormat;
    format->setCodec(codec);
    format->setSampleRate(sampleRate);

    format->setChannelCount(channels);
    format->setSampleSize(16);
    format->setSampleType(QAudioFormat::SignedInt);
    format->setByteOrder(QAudioFormat::LittleEndian);
    QAudioEncoderSettings temp;
 player->setEncodingSettings(settings, QVideoEncoderSettings(), container);

qDebug()<<player->audioSettings().bitRate();
qDebug()<<player->audioSettings().channelCount();
qDebug()<<player->audioSettings().encodingMode();
qDebug()<<player->audioSettings().codec();
qDebug()<<player->audioSettings().sampleRate();




}

void audiorecorder::togglePlay()
{
    if (player->state() != QMediaRecorder::RecordingState)

     player->record();
    else
       player->pause();
    qDebug()<<player->state();
}

QAudioFormat audiorecorder::getFormat()
{
    return *format;
}


