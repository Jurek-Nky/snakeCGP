// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

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

class GeometryEngine;

enum Directions {
    LEFT, RIGHT, UP, DOWN
};

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;

    MainWidget(QWidget *parent = 0);

    ~MainWidget();

private slots:

    void animateGL();

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
