// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "snakegeometry.h"

class SnakeGeometry;

class GeometryEngine : protected QOpenGLFunctions {
public:
    GeometryEngine();

    virtual ~GeometryEngine();

    void drawPlaneGeometry(QOpenGLShaderProgram *program);

    void drawGeometries(QOpenGLShaderProgram *program);

private:

    void initPlaneGeometry();

    QOpenGLBuffer planeArrayBuf;
    QOpenGLBuffer planeIndexBuf;

    SnakeGeometry *snake = nullptr;
};

#endif // GEOMETRYENGINE_H
