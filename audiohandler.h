#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <QMediaPlayer>
#include <QAudioOutput>

class audioHandler
{
public:
    audioHandler();

    QAudioOutput * audioOut;
    QMediaPlayer * music;
    QMediaPlayer * soundBufferA;
    ///likely reserved for level up sound
    QMediaPlayer * soundBufferB;

    void playMusic(QUrl audioSource, int volume = 100);
    void playSFXBufferA(QUrl audioSource, int volume = 100);
    void playSFXBufferB(QUrl audioSource, int volume = 100);
};

#endif // AUDIOHANDLER_H
