#ifndef SNAKECGP_WIDGETSTACK_H
#define SNAKECGP_WIDGETSTACK_H

#include "../audio/soundengine.h"
#include "gameoverwidget.h"
#include "gamewidget.h"
#include "helpwidget.h"
#include "menuwidget.h"
#include <QOpenGLFunctions>
#include <QStackedWidget>

class WidgetStack : public QWidget {
  Q_OBJECT
public:
  using QWidget = QWidget;

  explicit WidgetStack(QWidget *parent = 0);

  virtual ~WidgetStack();

public slots:

  void closeMenu();

  void openMenu();

  void openHelp();

  void gameOver();

  void toggleMaximized();

  void restartGame();

  void foodConsumed();

protected:
  void keyPressEvent(QKeyEvent *e) override;

signals:

  void resumeGame();

private:
  QStackedWidget *stack = nullptr;

  MenuWidget *menu = nullptr;

  GameWidget *game = nullptr;

  HelpWidget *help = nullptr;

  GameOverWidget *gameOverWidget = nullptr;

  SoundEngine *soundEngine = nullptr;
  void connections();
};

#endif // SNAKECGP_WIDGETSTACK_H
