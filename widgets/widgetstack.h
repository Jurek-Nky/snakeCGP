#ifndef SNAKECGP_WIDGETSTACK_H
#define SNAKECGP_WIDGETSTACK_H


#include <QStackedWidget>
#include <QOpenGLFunctions>
#include "menuwidget.h"
#include "openglwidget.h"
#include "../audio/soundengine.h"
#include "gameoverwidget.h"

class WidgetStack : public QWidget {
Q_OBJECT
public:
    using QWidget = QWidget;

    explicit WidgetStack(QWidget *parent = 0);

    virtual ~WidgetStack();

public slots:

    void closeMenu();

    void openMenu();

    void gameOver();

    void toggleMaximized();

protected:

    void keyPressEvent(QKeyEvent *e) override;

signals:

    void resumeGame();

private:
    QStackedWidget *stack = nullptr;
    MenuWidget *menu = nullptr;
    GameWidget *game = nullptr;
    GameOverWidget *gameOverWidget = nullptr;
    SoundEngine *soundEngine = nullptr;
};


#endif //SNAKECGP_WIDGETSTACK_H
