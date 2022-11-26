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
    QMediaPlayer *player;

public slots:
    void playbackDurationChanged(qint64);
};


#endif //SNAKECGP_SOUNDENGINE_H
