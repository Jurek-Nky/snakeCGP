//
// Created by jurek on 26.11.22.
//

#ifndef SNAKECGP_SOUNDENGINE_H
#define SNAKECGP_SOUNDENGINE_H

#include <QWidget>
#include <QtMultimedia/QMediaPlayer>

class SoundEngine : public QWidget {
  Q_OBJECT
public:
  SoundEngine();

  void playMusic();

private:
  QMediaPlayer *musicPlayer;
  QAudioOutput *musicOutput;
  QMediaPlayer *effectPlayer;
  QAudioOutput *effectOutput;

public slots:

  void updateVolumes();

  void playbackDurationChanged(qint64);

  void playEatingSound();

  void playMenuMusic();

  void playGameOver();
};

#endif // SNAKECGP_SOUNDENGINE_H
