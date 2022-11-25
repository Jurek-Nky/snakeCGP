// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "geometryengine.h"

#include <QVector3D>
#include <iostream>

struct VertexData {
    QVector3D position;
    QVector2D texCoord;
};

//! [0]
GeometryEngine::GeometryEngine()
        : planeIndexBuf(QOpenGLBuffer::IndexBuffer) {
    initializeOpenGLFunctions();

    snake = new SnakeGeometry;

    initPlaneGeometry();
}

GeometryEngine::~GeometryEngine() {
    planeArrayBuf.destroy();
    planeIndexBuf.destroy();
}
//! [0]

void GeometryEngine::initPlaneGeometry() {
    VertexData vertices[] = {
            {QVector3D(-1, 0, -1), QVector2D(0.f, 0.f)},
            {QVector3D(-1, 0, 1),  QVector2D(0.f, 0.66f)},
            {QVector3D(1, 0, 1),   QVector2D(0.5f, 0.66f)},
            {QVector3D(1, 0, -1),  QVector2D(0.5f, 0.f)},
    };
    GLushort indices[] = {
            0, 1, 2, 3
    };

    planeArrayBuf.bind();
    planeArrayBuf.allocate(vertices, 4 * sizeof(VertexData));

    planeIndexBuf.bind();
    planeIndexBuf.allocate(indices, 4 * sizeof(vertices));

}

void GeometryEngine::drawPlaneGeometry(QOpenGLShaderProgram *program) {
    planeArrayBuf.bind();
    planeIndexBuf.bind();

    qintptr offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, nullptr);
}

void GeometryEngine::drawGeometries(QOpenGLShaderProgram *program) {
    snake->drawSnakeGeometry(program);
}
