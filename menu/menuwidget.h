#ifndef SNAKECGP_MENUWIDGET_H
#define SNAKECGP_MENUWIDGET_H

#include <QWidget>
#include "options.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWidget; }
QT_END_NAMESPACE


class MenuWidget : public QWidget {
Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent);

    ~MenuWidget() override;

public slots:

    static void changeMusicLevel(int);

    static void changeSoundEffectLevel(int);

    static void changeSoundOverallLevel(int);

    void setMusicEnabled(bool);

    void setSoundEffectsEnabled(bool);

    void setSoundEnabled(bool);



private:
    Ui::MenuWidget *ui;
};


#endif //SNAKECGP_MENUWIDGET_H
