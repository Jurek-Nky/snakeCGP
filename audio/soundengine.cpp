#include "soundengine.h"
#include "../options.h"
#include <QAudioDevice>
#include <QAudioOutput>
#include <iostream>

SoundEngine::SoundEngine() {
  musicPlayer = new QMediaPlayer;
  musicOutput = new QAudioOutput;
  musicPlayer->setAudioOutput(musicOutput);
  musicPlayer->setSource(QUrl("qrc:/audio/music.ogg"));
  musicOutput->setVolume(float(Options::musicLevel) / 100.0f);
  musicPlayer->play();
  musicPlayer->setLoops(QMediaPlayer::Infinite);
  }

void SoundEngine::playMusic() {}

void SoundEngine::playbackDurationChanged(qint64 duration) {}

void SoundEngine::updateVolumes() {
  musicOutput->setMuted(!Options::musicEnabled);
  musicOutput->setVolume(float(Options::musicLevel) / 100.0f);
}

void SoundEngine::playEatingSound() {
  effectPlayer = new QMediaPlayer;
  effectOutput = new QAudioOutput;
  effectPlayer->setAudioOutput(effectOutput);
  effectOutput->setVolume(float(Options::soundEffectLevel) / 100.0f);
  effectPlayer->setSource(QUrl("qrc:/audio/eating.wav"));
  effectPlayer->play();
}

void SoundEngine::playMenuMusic() {
}

void SoundEngine::playGameOver() {
  musicPlayer->setSource(QUrl("qrc:/audio/gameOver.wav"));
  musicPlayer->play();
  musicPlayer->setLoops(QMediaPlayer::Once);
}
