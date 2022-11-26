//
// Created by jurek on 26.11.22.
//

#include <iostream>
#include <QAudioOutput>
#include <QAudioDevice>
#include "soundengine.h"
#include "../menu/options.h"

SoundEngine::SoundEngine() {


    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
//    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setSource(QUrl::fromLocalFile("/home/jurek/git/snakeCGP/audio/music.mp3"));
    audioOutput->setVolume(float(Options::musicLevel) / 100.0f);
    player->play();
}

void SoundEngine::playbackDurationChanged(qint64 d) {
}

void SoundEngine::playMusic() {

}

void SoundEngine::updateAudio() {
    audioOutput->setMuted(!Options::musicEnabled);
    audioOutput->setVolume(float(Options::musicLevel) / 100.0f);

}
