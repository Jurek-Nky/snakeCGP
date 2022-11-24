// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void drawCubeGeometry(QOpenGLShaderProgram *program);

    void drawPlaneGeometry(QOpenGLShaderProgram *program);

private:
    void initCubeGeometry();
    void initPlaneGeometry();

    QOpenGLBuffer cubeArrayBuf;
    QOpenGLBuffer cubeIndexBuf;
    QOpenGLBuffer planeArrayBuf;
    QOpenGLBuffer planeIndexBuf;
};

#endif // GEOMETRYENGINE_H
