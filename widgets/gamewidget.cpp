#include "gamewidget.h"
#include "widgetstack.h"

#include <QMouseEvent>

#include <cmath>
#include <iostream>

GameWidget::GameWidget(QWidget *parent)
        : QOpenGLWidget(parent),
          updateTimer(this),
          stopWatch(),
          snakeHead(nullptr),
          plane(nullptr) {

    QObject::connect(&updateTimer, SIGNAL(timeout()), this, SLOT(animateGL()));
    // 16ms => 60 fps
    updateTimer.start(16);
    stopWatch.start();

    connect(this, SIGNAL(openMenu()), parentWidget(), SLOT(openMenu()));
    connect(this, SIGNAL(gameOver()), parentWidget(), SLOT(gameOver()));
    connect(this, SIGNAL(toggleMaximized()), parentWidget(), SLOT(toggleMaximized()));
}

GameWidget::~GameWidget() {
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
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
    snakeHeadPos = QVector3D(std::fmod(random(), Options::boardSize - 2.0f) + 1.0f,
                             std::fmod(random(), Options::boardSize - 2.0f) + 1.0f,
                             0.0f);
    // creating the viewMatrix, that represents the center of the playing field
    viewMatrix = QMatrix4x4();
    viewMatrix.translate(0.0, 0.0, -Options::boardSize * 2);
    viewMatrix.rotate(QQuaternion::fromAxisAndAngle(QVector3D(0.0, 0.0, 1.0), 45));
    viewMatrix.rotate(QQuaternion::fromAxisAndAngle(QVector3D(-1.0, 1.0, 0.0), 55));

    QMatrix4x4 snakeHeadMatrix = viewMatrix;
    // move snakeHeadMatrix to the bottom left corner
    snakeHeadMatrix.translate(std::floor(-Options::boardSize / 2) - 1, std::floor(-Options::boardSize / 2) - 1, 0.f);
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
    planeMatrix.scale(Options::boardSize + 1.0f + 0.5f, Options::boardSize + 1.0f + 0.5f, 0.0f);
    plane = new PlaneGeometry(planeMatrix);
}

void GameWidget::generateNewFood() {
    foodPos = QVector3D(std::fmod(random(), Options::boardSize - 2.0f) + 1.0f,
                        std::fmod(random(), Options::boardSize - 2.0f) + 1.0f,
                        0.0f);

    // regenerate position as long as the food is on the snake
    // both checks are needed because checkCollision doesn't check the head and
    // checkFoodCollision only checks the head of the snake to save time
    while (snakeHead->checkCollision(foodPos) or snakeHead->checkFoodCollision(foodPos)) {
        foodPos = QVector3D(std::fmod(random(), Options::boardSize - 2.0f) + 1.0f,
                            std::fmod(random(), Options::boardSize - 2.0f) + 1.0f,
                            0.0f);
    }

    QMatrix4x4 foodMatrix = viewMatrix;
    // move foodMatrix to the bottom left corner
    foodMatrix.translate(std::round(-Options::boardSize / 2), std::round(-Options::boardSize / 2), 0.f);
    // foodMatrix needs to be translated to the foodPosition
    foodMatrix.translate(foodPos);
    food = new FoodGeometry(foodMatrix);
}

void GameWidget::initShaders() {
    program.removeAllShaders();
    // Compile vertex shaders
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.glsl"))
        close();

    // Compile fragment shaders
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.glsl"))
        close();

    // Link shaders pipeline
    if (!program.link())
        close();

    // Bind shaders pipeline for use
    if (!program.bind())
        close();
}


void GameWidget::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        case Qt::Key_Right:
        case Qt::Key_L:
            if (direction != LEFT) {
                direction = RIGHT;
            }
            break;
        case Qt::Key_Left:
        case Qt::Key_H:
            if (direction != RIGHT) {
                direction = LEFT;
            }
            break;
        case Qt::Key_Up:
        case Qt::Key_K:
            if (direction != DOWN) {
                direction = UP;
            }
            break;
        case Qt::Key_Down:
        case Qt::Key_J:
            if (direction != UP) {
                direction = DOWN;
            }
            break;
        case Qt::Key_Space:
            Options::running = !Options::running;
            break;
        case Qt::Key_Comma:
            singleStep = true;
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

    }
}

void GameWidget::keyReleaseEvent(QKeyEvent *e) {
}

void GameWidget::mousePressEvent(QMouseEvent *e) {
}

void GameWidget::mouseReleaseEvent(QMouseEvent *e) {
}

void GameWidget::timerEvent(QTimerEvent *timerEvent) {
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

void GameWidget::animateGL() {
    qint64 timeElapsedMs = stopWatch.nsecsElapsed() / 1000000;
    if (singleStep && !Options::running) {
        moveSnakeHead();
        update();
        singleStep = false;
    } else if (timeElapsedMs > 150 && Options::running) {
        stopWatch.restart();
        moveSnakeHead();
        update();
    }
    update();
}

void GameWidget::moveSnakeHead() {
    switch (direction) {
        case RIGHT:
            snakeHeadPos.setX(snakeHeadPos.x() + 1.0f);
            break;
        case LEFT:
            snakeHeadPos.setX(snakeHeadPos.x() - 1.0f);
            break;
        case UP:
            snakeHeadPos.setY(snakeHeadPos.y() + 1.0f);
            break;
        case DOWN:
            snakeHeadPos.setY(snakeHeadPos.y() - 1.0f);
            break;
    }
    QMatrix4x4 snakeHeadMatrix = viewMatrix;
    snakeHeadMatrix.translate(floor(-Options::boardSize / 2), floor(-Options::boardSize / 2), 0.f);
    snakeHeadMatrix.translate(snakeHeadPos);
    snakeHead->move(snakeHeadMatrix, snakeHeadPos);

    if (snakeHeadPos.x() < 0 || snakeHeadPos.x() > Options::boardSize - 1 ||
        snakeHeadPos.y() < 0 || snakeHeadPos.y() > Options::boardSize - 1) {
        Options::running = false;
        emit gameOver();
    }

    // check if snakeHead collides with itself
    if (snakeHead->checkCollision(snakeHeadPos)) {
        Options::running = false;
        emit gameOver();
    }

    // call checkCollision on snakeHead and create new food if return value is true
    if (snakeHead->checkFoodCollision(foodPos)) {
        generateNewFood();
        update();
        snakeHead->addChild();
    }
}

void GameWidget::resume() {
    Options::running = true;
}

void GameWidget::pause() {
    Options::running = false;
}
