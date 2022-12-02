#include <QVBoxLayout>
#include <QKeyEvent>
#include <iostream>
#include "widgetstack.h"
#include "menu/menuwidget.h"
#include "game/gamewidget.h"
#include "menu/gameoverwidget.h"

WidgetStack::WidgetStack(QWidget *parent) : QWidget(parent) {

    setMinimumSize(1400, 800);

    menu = new MenuWidget(this);
    game = new GameWidget(this);
    gameOverWidget = new GameOverWidget(this);
    stack = new QStackedWidget;

    soundEngine = new SoundEngine();

    stack->addWidget(game);
    stack->addWidget(menu);
    stack->addWidget(gameOverWidget);

    auto *layout = new QVBoxLayout;
    layout->addWidget(stack);
    setLayout(layout);
    stack->setFocusPolicy(Qt::FocusPolicy::TabFocus);
    stack->setCurrentWidget(game);
    game->setFocus();

    connect(this, SIGNAL(resumeGame()), game, SLOT(resume()));

    connect(menu, SIGNAL(updateAudio()), soundEngine, SLOT(updateAudio()));
}

WidgetStack::~WidgetStack() {

}

void WidgetStack::keyPressEvent(QKeyEvent *e) {

    switch (e->key()) {
        case Qt::Key_Escape:
            if (stack->currentWidget() == menu) {
                stack->setCurrentWidget(game);
                game->setFocus();
                resumeGame();

            } else {
                stack->setCurrentWidget(menu);
            }
            break;
    }
}

void WidgetStack::closeMenu() {
    stack->setCurrentWidget(game);
    game->setFocus();
}

void WidgetStack::openMenu() {
    stack->setCurrentWidget(menu);
    menu->setFocus();
}

// open gameOverWidget and play GameOverWidget sound
void WidgetStack::gameOver() {
    stack->setCurrentWidget(gameOverWidget);
    gameOverWidget->setFocus();
    soundEngine->playGameOver();
}
