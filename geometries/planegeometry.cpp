#include <iostream>
#include "planegeometry.h"
#include "vertexData.h"


PlaneGeometry::PlaneGeometry(QMatrix4x4 model)
        : arrayBuffer(QOpenGLBuffer::VertexBuffer),
          texture(nullptr) {
    initializeOpenGLFunctions();
    arrayBuffer.create();

    modelMatrix = model;
    initPlaneGeometry();
}

PlaneGeometry::~PlaneGeometry() {
    arrayBuffer.destroy();
    if (texture) {
        delete texture;
        texture = nullptr;
    }
}

void PlaneGeometry::initPlaneGeometry() {
    initTexture();
    initVertex();
}

void PlaneGeometry::initTexture() {
    texture = new QOpenGLTexture(QImage(":/resources/brick.png").mirrored());
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void PlaneGeometry::initVertex() {
    VertexData vertices[] = {
            {QVector3D(-0.5f, -0.5f, 0.0f), QVector2D(0.0f, 0.0f)},
            {QVector3D(0.5f, -0.5f, 0.0f),  QVector2D(1.0f, 0.0f)},
            {QVector3D(0.5f, 0.5f, 0.0f),   QVector2D(1.0f, 1.0f)},

            {QVector3D(-0.5f, -0.5f, 0.0f), QVector2D(0.0f, 0.0f)},
            {QVector3D(-0.5f, 0.5f, 0.0f),  QVector2D(0.0f, 1.0f)},
            {QVector3D(0.5f, 0.5f, 0.0f),   QVector2D(1.0f, 1.0f)},
    };
    arrayBuffer.bind();
    arrayBuffer.allocate(vertices, sizeof(vertices));
}


void PlaneGeometry::drawPlaneGeometry(QOpenGLShaderProgram *program, QMatrix4x4 projection) {
    program->setUniformValue("mvp_matrix", projection * modelMatrix);

    arrayBuffer.bind();

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

    texture->bind();
    program->setUniformValue("texture", 0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, arrayBuffer.size());
}

