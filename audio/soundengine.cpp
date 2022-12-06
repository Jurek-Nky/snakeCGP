#include "soundengine.h"
#include "../options.h"
#include <QAudioDevice>
#include <QAudioOutput>
#include <iostream>

SoundEngine::SoundEngine() {

  effectOutput = new QAudioOutput;
  effectPlayer = new QMediaPlayer;
  effectPlayer->setAudioOutput(effectOutput);
  effectOutput->setVolume(float(Options::soundEffectLevel) / 100.0f);

  musicPlayer = new QMediaPlayer;
  musicOutput = new QAudioOutput;
  musicPlayer->setAudioOutput(musicOutput);
  musicPlayer->setSource(QUrl("qrc:/audio/music.mp3"));
  musicOutput->setVolume(float(Options::musicLevel) / 100.0f);
  musicPlayer->play();
}

void SoundEngine::playbackDurationChanged(qint64 d) {}

void SoundEngine::playMusic() {}

void SoundEngine::updateAudio() {
  musicOutput->setMuted(!Options::musicEnabled);
  musicOutput->setVolume(float(Options::musicLevel) / 100.0f);

  effectOutput->setMuted(!Options::soundEffectsEnabled);
  effectOutput->setVolume(float(Options::soundEffectLevel) / 100.0f);
}

void SoundEngine::playEatingSound() {
  effectPlayer->setSource(QUrl::fromLocalFile(""));
  effectPlayer->play();
}

void SoundEngine::playMenuMusic() {
  musicPlayer->setSource(QUrl("qrc:/audio/menuMusic.mp3"));
  musicPlayer->play();
}

void SoundEngine::playGameOver() {
  musicPlayer->setSource(QUrl("qrc:/audio/gameOver.mp3"));
  musicPlayer->play();
}
