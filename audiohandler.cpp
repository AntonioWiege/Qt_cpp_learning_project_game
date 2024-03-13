#include "audiohandler.h"

audioHandler::audioHandler() {
    soundBufferA=nullptr;
    soundBufferB=nullptr;
    music=nullptr;
}

void audioHandler::playSFXBufferA(QUrl audioSource, int volume)
{
    if(soundBufferA==nullptr){
        soundBufferA = new QMediaPlayer();
        audioOut = new QAudioOutput;
        soundBufferA->setAudioOutput(audioOut);
        soundBufferA->setLoops(1);
    }
    soundBufferA->setPosition(0);
    soundBufferA->setSource(audioSource);
    audioOut->setVolume(volume);
    soundBufferA->play();
}

void audioHandler::playSFXBufferB(QUrl audioSource, int volume)
{
    if(soundBufferB==nullptr){
        soundBufferB = new QMediaPlayer();
        audioOut = new QAudioOutput;
        soundBufferB->setAudioOutput(audioOut);
        soundBufferB->setLoops(1);
    }
    soundBufferB->setPosition(0);
    soundBufferB->setSource(audioSource);
    audioOut->setVolume(volume);
    soundBufferB->play();
}

void audioHandler::playMusic(QUrl audioSource, int volume)
{
    if(music==nullptr){
        music = new QMediaPlayer();
        audioOut = new QAudioOutput;
        music->setAudioOutput(audioOut);
        music->setLoops(-1);
    }
    music->setSource(audioSource);
    audioOut->setVolume(volume);
    music->play();
}
