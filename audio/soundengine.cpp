//
// Created by jurek on 26.11.22.
//

#include <iostream>
#include <QAudioOutput>
#include <QAudioDevice>
#include "soundengine.h"

SoundEngine::SoundEngine() {
    player = new QMediaPlayer;

    player->setSource(QUrl("/home/jurek/git/snakeCGP/audio/music.mp3"));

    QAudioOutput audioOutput = QAudioOutput();
    player->setAudioOutput(&audioOutput);
    player->audioOutput()->setVolume(0.8f);
    player->audioOutput()->setMuted(false);
    player->play();
    std::cout << player->audioOutput()->device().description().toStdString() << std::endl;
    std::cout << player->audioOutput()->volume() << std::endl;
    std::cout << player->source().toString().toStdString() << std::endl;
    std::cout << player->errorString().toStdString() << std::endl;


    connect(this->player, SIGNAL(durationChanged(qint64)), this, SLOT(playbackDurationChanged(qint64)));
}

void SoundEngine::playbackDurationChanged(qint64 d) {
    std::cout << d << std::endl;
    std::cout << player->duration() << std::endl;
}

void SoundEngine::playMusic() {

}

