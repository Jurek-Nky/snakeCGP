#include "gamewidget.h"
#include "widgetstack.h"

#include <QMouseEvent>

#include <cmath>
#include <iostream>

GameWidget::GameWidget(QWidget *parent)
    : QOpenGLWidget(parent), updateTimer(this), snakeHead(nullptr),
      plane(nullptr) {

  QObject::connect(&updateTimer, SIGNAL(timeout()), this,
                   SLOT(updateSnakeHead()));
  updateTimer.start(Options::speed);
  connect(this, SIGNAL(openMenu()), parentWidget(), SLOT(openMenu()));
  connect(this, SIGNAL(gameOver()), parentWidget(), SLOT(gameOver()));
  connect(this, SIGNAL(openHelp()), parentWidget(), SLOT(openHelp()));
  connect(this, SIGNAL(toggleMaximized()), parentWidget(),
          SLOT(toggleMaximized()));
  connect(this, SIGNAL(foodConsumed()), parentWidget(), SLOT(foodConsumed()));
}

GameWidget::~GameWidget() {
  // Make sure the context is current when deleting the texture
  // and the buffers.
  makeCurrent();
  delete texture;
  delete snakeHead;
  delete food;
  delete plane;
  doneCurrent();
}

void GameWidget::initializeGL() {
  initializeOpenGLFunctions();

  glClearColor(0, 0, 0, 1);
  initShaders();

  // Enable depth buffer
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // Enable back face culling
  glEnable(GL_CULL_FACE);

  setWindowTitle("Snake");

  initComponents();

  time_t nTime;
  srandom(time(&nTime));
}

void GameWidget::initComponents() {
  // initialize start point for the snake head
  snakeHeadPos =
      QVector3D(Options::boardSize / 2.0f, Options::boardSize / 2.0f, 0.0f);
  // creating the viewMatrix, that represents the center of the playing field
  viewMatrix = QMatrix4x4();
  viewMatrix.translate(0.0, 0.0, -Options::boardSize * 2);
  viewMatrix.rotate(
      QQuaternion::fromAxisAndAngle(QVector3D(0.0, 0.0, 1.0), 45));
  viewMatrix.rotate(
      QQuaternion::fromAxisAndAngle(QVector3D(-1.0, 1.0, 0.0), 55));

  QMatrix4x4 snakeHeadMatrix = viewMatrix;
  // move snakeHeadMatrix to the bottom left corner
  snakeHeadMatrix.translate(std::floor(-Options::boardSize / 2) - 1,
                            std::floor(-Options::boardSize / 2) - 1, 0.f);
  // snakeHeadMatrix needs to be translated to the snakeHeadPosition
  snakeHeadMatrix.translate(snakeHeadPos);
  snakeHead = new SnakeGeometry(snakeHeadMatrix);
  snakeHead->isHead = true;

  generateNewFood();

  // create modelMatrix for the playing field and create the field
  QMatrix4x4 planeMatrix = viewMatrix;
  planeMatrix.translate(0.0, 0.0, -1.0);
  if (std::fmod(Options::boardSize, 2.0f) != 1) {
    planeMatrix.translate(0.5f, 0.5f, 0.0f);
  }
  planeMatrix.scale(Options::boardSize + 1.0f + 0.5f,
                    Options::boardSize + 1.0f + 0.5f, 0.0f);
  plane = new PlaneGeometry(planeMatrix);
}

void GameWidget::generateNewFood() {
  Options::score += 1;
  emit foodConsumed();
  foodPos =
      QVector3D(std::fmod(random(), Options::boardSize - 2.0f) + 1.0f,
                std::fmod(random(), Options::boardSize - 2.0f) + 1.0f, 0.0f);

  // regenerate position as long as the food is on the snake
  // both checks are needed because checkCollision doesn't check the head and
  // checkFoodCollision only checks the head of the snake to save time
  while (snakeHead->checkCollision(foodPos) or
         snakeHead->checkFoodCollision(foodPos)) {
    foodPos =
        QVector3D(std::fmod(random(), Options::boardSize - 2.0f) + 1.0f,
                  std::fmod(random(), Options::boardSize - 2.0f) + 1.0f, 0.0f);
  }

  QMatrix4x4 foodMatrix = viewMatrix;
  // move foodMatrix to the bottom left corner
  foodMatrix.translate(std::floor(-Options::boardSize / 2) - 1,
                       std::floor(-Options::boardSize / 2) - 1, 0.f);
  // foodMatrix needs to be translated to the foodPosition
  foodMatrix.translate(foodPos);
  food = new FoodGeometry(foodMatrix);

  if (Options::speed > 100 && Options::score % 5 == 0) {
    Options::speed = Options::speed - 5;
    updateTimer.start(Options::speed);
  }
}

void GameWidget::initShaders() {
  program.removeAllShaders();
  // Compile vertex shaders
  if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                       ":/shaders/vshader.glsl"))
    close();

  // Compile fragment shaders
  if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                       ":/shaders/fshader.glsl"))
    close();

  // Link shaders pipeline
  if (!program.link())
    close();

  // Bind shaders pipeline for use
  if (!program.bind())
    close();
}

void GameWidget::resizeGL(int w, int h) {
  // Calculate aspect ratio
  qreal aspect = qreal(w) / qreal(h ? h : 1);

  // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
  const qreal zNear = 0.01, zFar = 100.0, fov = 45.0;

  // Reset projection
  projection.setToIdentity();

  // Set perspective projection
  projection.perspective(fov, aspect, zNear, zFar);
}

void GameWidget::paintGL() {
  // Clear color and depth buffer
  initShaders();
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // call draw on all components
  // snakeHead calls all its children
  plane->drawPlaneGeometry(&program, projection);
  snakeHead->drawSnakeGeometry(&program, projection);
  food->drawFoodGeometry(&program, projection);
}

void GameWidget::updateSnakeHead() {
  if (!Options::running) {
    return;
  }
  Directions oldDirection = direction;
  direction = newDirection;
  if (snakeHead->checkFoodCollision(foodPos)) {
    snakeHead->addChild();
    generateNewFood();
  }
  switch (direction) {
  case UP:
    snakeHeadPos.setY(snakeHeadPos.y() + 1.0f);
    snakeHead->newOrientation(Y, oldDirection, direction);
    break;
  case DOWN:
    snakeHeadPos.setY(snakeHeadPos.y() - 1.0f);
    snakeHead->newOrientation(Y, oldDirection, direction);
    break;
  case LEFT:
    snakeHeadPos.setX(snakeHeadPos.x() - 1.0f);
    snakeHead->newOrientation(X, oldDirection, direction);
    break;
  case RIGHT:
    snakeHeadPos.setX(snakeHeadPos.x() + 1.0f);
    snakeHead->newOrientation(X, oldDirection, direction);
    break;
  }
  if (snakeHead->checkCollision(snakeHeadPos)) {
    std::cout << "snake collided with itself" << std::endl;
    Options::running = false;
    emit gameOver();
  }
  if (snakeHeadPos.x() > Options::boardSize + 1 || snakeHeadPos.x() < 1 ||
      snakeHeadPos.y() > Options::boardSize + 1 || snakeHeadPos.y() < 1) {
    std::cout << "snake collided with wall" << std::endl;
    Options::running = false;
    emit gameOver();
  }

  QMatrix4x4 snakeHeadMatrix = viewMatrix;
  // move snakeHeadMatrix to the bottom left corner
  snakeHeadMatrix.translate(std::floor(-Options::boardSize / 2) - 1,
                            std::floor(-Options::boardSize / 2) - 1, 0.f);
  snakeHead->move(snakeHeadPos, snakeHeadMatrix);
  update();
}

void GameWidget::resume() { Options::running = true; }

void GameWidget::pause() { Options::running = false; }

void GameWidget::wheelEvent(QWheelEvent *e) {
  float delta = e->angleDelta().y() / 100.0f;
  Options::camZoom += delta;
  if (Options::camZoom > 30.0f) {
    Options::camZoom = 30.0f;
    return;
  } else if (Options::camZoom < -30) {
    Options::camZoom = -30;
    return;
  }
  projection.translate(0.0f, 0.0f, delta);
}
void GameWidget::keyPressEvent(QKeyEvent *e) {
  switch (e->key()) {
  case Qt::Key_Right:
  case Qt::Key_L:
  case Qt::Key_D:
    if (direction != LEFT) {
      newDirection = RIGHT;
    }
    break;
  case Qt::Key_Left:
  case Qt::Key_H:
  case Qt::Key_A:
    if (direction != RIGHT) {
      newDirection = LEFT;
    }
    break;
  case Qt::Key_Up:
  case Qt::Key_K:
  case Qt::Key_W:
    if (direction != DOWN) {
      newDirection = UP;
    }
    break;
  case Qt::Key_Down:
  case Qt::Key_J:
  case Qt::Key_S:
    if (direction != UP) {
      newDirection = DOWN;
    }
    break;
  case Qt::Key_Space:
    Options::running = !Options::running;
    break;
  case Qt::Key_Q:
    exit(0);
    break;
  case Qt::Key_F:
    emit toggleMaximized();
    break;
  case Qt::Key_Escape:
    Options::running = false;
    emit openMenu();
    break;
  case Qt::Key_M:
    Options::soundEnabled = !Options::soundEnabled;
    emit updateAudio();
    break;
  case Qt::Key_Question:
    Options::running = false;
    emit openHelp();
    break;
  }
}
void GameWidget::keyReleaseEvent(QKeyEvent *e) {}

void GameWidget::mousePressEvent(QMouseEvent *e) {}

void GameWidget::mouseReleaseEvent(QMouseEvent *e) {}
