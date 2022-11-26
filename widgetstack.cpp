#include <QVBoxLayout>
#include <QKeyEvent>
#include <iostream>
#include "widgetstack.h"
#include "menu/menuwidget.h"
#include "game/gamewidget.h"

WidgetStack::WidgetStack(QWidget *parent) : QWidget(parent) {

    menu = new MenuWidget(this);
    game = new GameWidget(this);
    stack = new QStackedWidget;

    soundEngine = new SoundEngine();

    stack->addWidget(game);
    stack->addWidget(menu);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stack);
    setLayout(layout);
    stack->setFocusPolicy(Qt::FocusPolicy::TabFocus);
    stack->setCurrentWidget(game);
    game->setFocus();

    connect(this, SIGNAL(resumeGame()), game, SLOT(resume()));
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