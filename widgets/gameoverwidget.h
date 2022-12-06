//
// Created by jurek on 02.12.22.
//

#ifndef SNAKECGP_GAMEOVERWIDGET_H
#define SNAKECGP_GAMEOVERWIDGET_H

#include <QWidget>

class GameOverWidget : public QWidget {
  Q_OBJECT

public:
  using QWidget = QWidget;

  explicit GameOverWidget(QWidget *parent = nullptr);

  ~GameOverWidget() override;

private:
};

#endif // SNAKECGP_GAMEOVERWIDGET_H
