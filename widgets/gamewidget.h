#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "../geometries/FoodGeometry.h"
#include "../geometries/planegeometry.h"
#include "../geometries/snakegeometry.h"
#include "../geometries/Skybox.h"
#include "../options.h"

#include <QBasicTimer>
#include <QElapsedTimer>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QTimer>
#include <QVector2D>

class GameWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  using QOpenGLWidget::QOpenGLWidget;

  GameWidget(QWidget *parent);

  ~GameWidget();

private slots:

  void updateSnakeHead();

signals:

  void openMenu();

  void openHelp();

  void gameOver();

  void toggleMaximized();

  void foodConsumed();

  void updateAudio();

protected:
  void keyPressEvent(QKeyEvent *e) override;

  void keyReleaseEvent(QKeyEvent *e) override;

  void mousePressEvent(QMouseEvent *e) override;

  void mouseReleaseEvent(QMouseEvent *e) override;

  void wheelEvent(QWheelEvent *e) override;

  void initializeGL() Q_DECL_OVERRIDE;

  void resizeGL(int w, int h) Q_DECL_OVERRIDE;

  void paintGL() Q_DECL_OVERRIDE;

  void initShaders();

private:
  int score = 0;

  QTimer updateTimer;

  QTimer animationTimer;

  QOpenGLShaderProgram program;

  QOpenGLTexture *texture = nullptr;

  Directions direction;

  Directions newDirection;

  bool singleStep;

  QVector3D snakeHeadPos;

  QVector3D foodPos;

  SnakeGeometry *snakeHead = nullptr;

  PlaneGeometry *plane = nullptr;

  FoodGeometry *food = nullptr;

  Skybox *skybox = nullptr;

  QMatrix4x4 projection;

  QMatrix4x4 viewMatrix;

  void initComponents();

  void generateNewFood();

  void checkCollisions();

  void animateSnake();
};

#endif // MAINWIDGET_H
