#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "../geometries/snakegeometry.h"
#include "../geometries/planegeometry.h"

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

protected:
    void keyPressEvent(QKeyEvent *e) override;

    void keyReleaseEvent(QKeyEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;

    void mouseReleaseEvent(QMouseEvent *e) override;

    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;


    void initShaders();

    void initTextures();

private:

    QTimer _updateTimer;
    QElapsedTimer _stopWatch;

    QBasicTimer timer;
    QOpenGLShaderProgram program;

    QOpenGLTexture *texture = nullptr;

    QMatrix4x4 projection;

    float boardSize = 20;
    Directions direction;

    bool running;
    bool singleStep;

    QVector3D snakeHeadPos;

    SnakeGeometry *snakeHead = nullptr;
    PlaneGeometry *plane = nullptr;

    QMatrix4x4 viewMatrix;

    void moveSnakeHead();

    void initComponents();
};

#endif // MAINWIDGET_H
