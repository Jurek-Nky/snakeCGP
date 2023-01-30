#include "widgetstack.h"
#include <QKeyEvent>
#include <QVBoxLayout>
#include <iostream>

WidgetStack::WidgetStack(QWidget *parent) : QWidget(parent) {

  setMinimumSize(1400, 800);

  menu = new MenuWidget(this);
  game = new GameWidget(this);
  gameOverWidget = new GameOverWidget(this);
  help = new HelpWidget(this);
  stack = new QStackedWidget;

  soundEngine = new SoundEngine();

  stack->addWidget(game);
  stack->addWidget(menu);
  stack->addWidget(gameOverWidget);
  stack->addWidget(help);

  auto *layout = new QVBoxLayout;
  layout->addWidget(stack);
  setLayout(layout);
  stack->setFocusPolicy(Qt::FocusPolicy::TabFocus);
  stack->setCurrentWidget(game);
  game->setFocus();

  connections();
}
void WidgetStack::connections() {
  connect(menu, SIGNAL(updateAudio()), soundEngine, SLOT(updateVolumes()));
  connect(help, SIGNAL(closeHelp()), this, SLOT(closeMenu()));

  connect(game, SIGNAL(updateAudio()), soundEngine, SLOT(updateVolumes()));
  connect(game, SIGNAL(openMenu()), this, SLOT(openMenu()));
  connect(game, SIGNAL(gameOver()), this, SLOT(gameOver()));
  connect(game, SIGNAL(foodConsumed()), this, SLOT(foodConsumed()));
  connect(game, SIGNAL(openHelp()), this, SLOT(openHelp()));
  connect(game, SIGNAL(toggleMaximized()), this, SLOT(toggleMaximized()));

  connect(gameOverWidget, SIGNAL(restartGame()), this, SLOT(restartGame()));

  connect(menu, SIGNAL(closeMenu()), this, SLOT(closeMenu()));
}

WidgetStack::~WidgetStack() {}

void WidgetStack::keyPressEvent(QKeyEvent *e) {

  switch (e->key()) {
  case Qt::Key_Escape:
    if (stack->currentWidget() == help || stack->currentWidget() == menu) {
      stack->setCurrentWidget(game);
      game->setFocus();
      Options::running = true;

    } else {
      stack->setCurrentWidget(menu);
    }
    break;
  }
}

void WidgetStack::closeMenu() {
  stack->setCurrentWidget(game);
  game->setFocus();
  Options::running = true;
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

void WidgetStack::toggleMaximized() {
  isMaximized() ? showNormal() : showMaximized();
}
void WidgetStack::restartGame() {
  delete game;
  Options::score = 0;
  Options::speed = 200;
  game = new GameWidget(this);
  stack->addWidget(game);
  game->setFocus();
  Options::running = true;
  stack->setCurrentWidget(game);
  soundEngine->playMusic();
  connections();
}
void WidgetStack::foodConsumed() { soundEngine->playEatingSound(); }
void WidgetStack::openHelp() { stack->setCurrentWidget(help); }
