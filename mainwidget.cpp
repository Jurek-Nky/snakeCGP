// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mainwidget.h"

#include <QMouseEvent>

#include <cmath>
#include <iostream>

MainWidget::MainWidget(QWidget *parent) : QOpenGLWidget(parent), _updateTimer(this), _stopWatch() {
    QObject::connect(&_updateTimer, SIGNAL(timeout()), this, SLOT(animateGL()));
    _updateTimer.start(18);
    _stopWatch.start();
}

MainWidget::~MainWidget() {
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    doneCurrent();
}

void MainWidget::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        case Qt::Key_Right:
        case Qt::Key_L:
            direction = RIGHT;
            break;
        case Qt::Key_Left:
        case Qt::Key_H:
            direction = LEFT;
            break;
        case Qt::Key_Up:
        case Qt::Key_K:
            direction = UP;
            break;
        case Qt::Key_Down:
        case Qt::Key_J:
            direction = DOWN;
            break;
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *e) {
//    if (e->key() == Qt::Key_Right && cubeLocation.x() < 10) {
//        cubeLocation.setX(cubeLocation.x() + 1);
//    }
//    if (e->key() == Qt::Key_Left && cubeLocation.x() > 0) {
//
//        cubeLocation.setX(cubeLocation.x() - 1);
//    }
//    if (e->key() == Qt::Key_Up && cubeLocation.y() < 10) {
//        cubeLocation.setY(cubeLocation.y() + 1);
//    }
//    if (e->key() == Qt::Key_Down && cubeLocation.y() > 0) {
//        cubeLocation.setY(cubeLocation.y() - 1);
//    }

}

void MainWidget::mousePressEvent(QMouseEvent *e) {
    // Save mouse press position
    mousePressPosition = QVector2D(e->position());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e) {
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->position()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void MainWidget::timerEvent(QTimerEvent *timerEvent) {
}

void MainWidget::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;

    // Use QBasicTimer because it's faster than QTimer
    timer.start(12, this);
}

void MainWidget::initShaders() {
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void MainWidget::initTextures() {
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWidget::resizeGL(int w, int h) {
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.01, zFar = 100.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL() {
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

//! [6]
    // Calculate model view transformation
//    matrix.translate(0.0, 0.0, -5.0);
//    matrix.rotate(rotation);

    // Set modelview-projection matrix
//! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
//    geometries->drawCubeGeometry(&program);


    QMatrix4x4 matrix;
    matrix = QMatrix4x4();
    matrix.translate(0.0, 0.0, -boardSize * 2);
    matrix.rotate(QQuaternion::fromAxisAndAngle(QVector3D(0.0, 0.0, 1.0), 45));
    matrix.rotate(QQuaternion::fromAxisAndAngle(QVector3D(-1.0, 1.0, 0.0), 55));

    QMatrix4x4 cubMatrix = matrix;

    matrix.scale(boardSize / 2 + 1, boardSize / 2 + 1, 0.0);

    program.setUniformValue("mvp_matrix", projection * matrix);
    geometries->drawPlaneGeometry(&program);


    cubMatrix.translate(-boardSize / 2, -boardSize / 2);
    cubMatrix.translate(cubeLocation);

    program.setUniformValue("mvp_matrix", projection * cubMatrix);
    geometries->drawCubeGeometry(&program);
}

void MainWidget::animateGL() {
    float timeElapsedMs = _stopWatch.nsecsElapsed() / 1000000.0f;
    if (timeElapsedMs > 300) {
        _stopWatch.restart();
        switch (direction) {
            case RIGHT:
                cubeLocation.setX(cubeLocation.x() < boardSize ? cubeLocation.x() + 1 : cubeLocation.x());
                break;
            case LEFT:
                cubeLocation.setX(cubeLocation.x() > 0 ? cubeLocation.x() - 1 : cubeLocation.x());
                break;
            case UP:
                cubeLocation.setY(cubeLocation.y() < boardSize ? cubeLocation.y() + 1 : cubeLocation.y());
                break;
            case DOWN:
                cubeLocation.setY(cubeLocation.y() > 0 ? cubeLocation.y() - 1 : cubeLocation.y());
                break;
        }


        update();
    }
}




