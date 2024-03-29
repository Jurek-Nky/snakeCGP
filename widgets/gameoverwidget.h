#ifndef SNAKECGP_GAMEOVERWIDGET_H
#define SNAKECGP_GAMEOVERWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameOverWidget;
}
QT_END_NAMESPACE

class GameOverWidget : public QWidget {
  Q_OBJECT

public:
  explicit GameOverWidget(QWidget *parent);

  ~GameOverWidget() override;

private:
  Ui::GameOverWidget *ui;

  bool nameAdded = false;

  void fillTableFromFile();

public slots:
  void onNameButtonClicked();
  void onExitButtonClicked();

signals:
  void restartGame();

protected:
  void focusInEvent(QFocusEvent *event) override;
};

#endif // SNAKECGP_GAMEOVERWIDGET_H
