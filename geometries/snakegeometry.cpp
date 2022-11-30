#include <iostream>
#include "snakegeometry.h"
#include "vertexData.h"

SnakeGeometry::SnakeGeometry(QMatrix4x4 model)
        : indexBuffer(QOpenGLBuffer::IndexBuffer),
          texture(nullptr) {
    initializeOpenGLFunctions();
    arrayBuffer.create();
    indexBuffer.create();

    modelMatrix = model;
    initSnakeGeometry();
}

SnakeGeometry::~SnakeGeometry() {
    arrayBuffer.destroy();
    indexBuffer.destroy();
    if (texture) {
        delete texture;
        texture = nullptr;
    }
}

void SnakeGeometry::initTexture() {
    texture = new QOpenGLTexture(QImage(":/resources/cube.png").mirrored());
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void SnakeGeometry::initVertex() {
    VertexData vertices[] = {
            // Vertex data for face 0
            {QVector3D(-0.5f, -0.5f, 0.5f),  QVector2D(0.0f, 0.0f)},  // v0
            {QVector3D(0.5f, -0.5f, 0.5f),   QVector2D(0.33f, 0.0f)}, // v1
            {QVector3D(-0.5f, 0.5f, 0.5f),   QVector2D(0.0f, 0.5f)},  // v2
            {QVector3D(0.5f, 0.5f, 0.5f),    QVector2D(0.33f, 0.5f)}, // v3

            // Vertex data for face 1
            {QVector3D(0.5f, -0.5f, 0.5f),   QVector2D(0.0f, 0.5f)}, // v4
            {QVector3D(0.5f, -0.5f, -0.5f),  QVector2D(0.33f, 0.5f)}, // v5
            {QVector3D(0.5f, 0.5f, 0.5f),    QVector2D(0.0f, 1.0f)},  // v6
            {QVector3D(0.5f, 0.5f, -0.5f),   QVector2D(0.33f, 1.0f)}, // v7

            // Vertex data for face 2
            {QVector3D(0.5f, -0.5f, -0.5f),  QVector2D(0.66f, 0.5f)}, // v8
            {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(1.0f, 0.5f)},  // v9
            {QVector3D(0.5f, 0.5f, -0.5f),   QVector2D(0.66f, 1.0f)}, // v10
            {QVector3D(-0.5f, 0.5f, -0.5f),  QVector2D(1.0f, 1.0f)},  // v11

            // Vertex data for face 3
            {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.66f, 0.0f)}, // v12
            {QVector3D(-0.5f, -0.5f, 0.5f),  QVector2D(1.0f, 0.0f)},  // v13
            {QVector3D(-0.5f, 0.5f, -0.5f),  QVector2D(0.66f, 0.5f)}, // v14
            {QVector3D(-0.5f, 0.5f, 0.5f),   QVector2D(1.0f, 0.5f)},  // v15

            // Vertex data for face 4
            {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.33f, 0.0f)}, // v16
            {QVector3D(0.5f, -0.5f, -0.5f),  QVector2D(0.66f, 0.0f)}, // v17
            {QVector3D(-0.5f, -0.5f, 0.5f),  QVector2D(0.33f, 0.5f)}, // v18
            {QVector3D(0.5f, -0.5f, 0.5f),   QVector2D(0.66f, 0.5f)}, // v19

            // Vertex data for face 5
            {QVector3D(-0.5f, 0.5f, 0.5f),   QVector2D(0.33f, 0.5f)}, // v20
            {QVector3D(0.5f, 0.5f, 0.5f),    QVector2D(0.66f, 0.5f)}, // v21
            {QVector3D(-0.5f, 0.5f, -0.5f),  QVector2D(0.33f, 1.0f)}, // v22
            {QVector3D(0.5f, 0.5f, -0.5f),   QVector2D(0.66f, 1.0f)}  // v23
    };

    GLushort indices[] = {
            0, 1, 2, 3, 3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
            4, 4, 5, 6, 7, 7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
            8, 8, 9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
            12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
            16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
            20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    // Transfer vertex data to VBO 0
    arrayBuffer.bind();
    arrayBuffer.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuffer.bind();
    indexBuffer.allocate(indices, 34 * sizeof(GLushort));
}

void SnakeGeometry::initSnakeGeometry() {
    initTexture();
    initVertex();
}

void SnakeGeometry::drawSnakeGeometry(QOpenGLShaderProgram *program, QMatrix4x4 projection) {
    program->setUniformValue("mvp_matrix", projection * modelMatrix);

    arrayBuffer.bind();
    indexBuffer.bind();

    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    texture->bind();
    program->setUniformValue("texture", 0);

    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, nullptr);

    if (child != nullptr) {
        child->drawSnakeGeometry(program, projection);
    }
}

void SnakeGeometry::addChild() {
    if (child == nullptr) {
        child = new SnakeGeometry(modelMatrix);
        return;
    }
    child->addChild();
}

void SnakeGeometry::move(QMatrix4x4 parent) {
    if (child != nullptr) {
        child->move(modelMatrix);
    }
    modelMatrix = parent;
}
