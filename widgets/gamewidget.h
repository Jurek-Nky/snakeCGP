#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "../geometries/snakegeometry.h"
#include "../geometries/planegeometry.h"
#include "../geometries/FoodGeometry.h"
#include "../options.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTimer>
#include <QElapsedTimer>

enum Directions {
    LEFT, RIGHT, UP, DOWN
};

class GameWidget : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;

    GameWidget(QWidget *parent);

    ~GameWidget();

private
    slots:

    void animateGL();

    void resume();

    void pause();

signals:

    void openMenu();
    void gameOver();
    void toggleMaximized();

protected:
    void keyPressEvent(QKeyEvent *e) override;

    void keyReleaseEvent(QKeyEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;

    void mouseReleaseEvent(QMouseEvent *e) override;

    void timerEvent(QTimerEvent *e) override;

    void initializeGL() Q_DECL_OVERRIDE;

    void resizeGL(int w, int h) Q_DECL_OVERRIDE;

    void paintGL() Q_DECL_OVERRIDE;


    void initShaders();


private:

    QTimer updateTimer;
    QElapsedTimer stopWatch;

    QOpenGLShaderProgram program;

    QOpenGLTexture *texture = nullptr;


    Directions direction;

    bool singleStep;

    QVector3D snakeHeadPos;
    QVector3D foodPos;

    SnakeGeometry *snakeHead = nullptr;
    PlaneGeometry *plane = nullptr;
    FoodGeometry *food = nullptr;

    QMatrix4x4 projection;
    QMatrix4x4 viewMatrix;

    void updateSnakePosition();

    void initComponents();

    void generateNewFood();

    void checkCollisions();

    void moveSnakeHead();
};

#endif // MAINWIDGET_H
