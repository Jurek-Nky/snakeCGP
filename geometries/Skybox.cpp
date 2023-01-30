//
// Created by jurek on 30.11.22.
//

#include "FoodGeometry.h"
#include "vertexData.h"
#include <iostream>

// create buffers and call init functions
FoodGeometry::FoodGeometry(QMatrix4x4 model)
    : indexBuffer(QOpenGLBuffer::IndexBuffer), texture(nullptr) {
  initializeOpenGLFunctions();
  arrayBuffer.create();
  indexBuffer.create();

  modelMatrix = model;
  initFoodGeometry();
}

FoodGeometry::~FoodGeometry() {}

// draw the Model using the previously created buffers
void FoodGeometry::drawFoodGeometry(QOpenGLShaderProgram *program,
                                    QMatrix4x4 projection) {
  program->setUniformValue("mvp_matrix", projection * modelMatrix);
  program->setUniformValue("model_matrix", modelMatrix);
  arrayBuffer.bind();
  indexBuffer.bind();

  qintptr offset = 0;

  int vertexLocation = program->attributeLocation("a_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3,
                              sizeof(VertexData));

  texture->bind();
  program->setUniformValue("texture", 0);

  glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, nullptr);
}

void FoodGeometry::initFoodGeometry() {
  initTexture();
  initVertex();
}

// load texture from foodNormal.jpg file
void FoodGeometry::initTexture() {
  texture =
      new QOpenGLTexture(QImage(":/resources/textures/cube.png").mirrored());
  texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  texture->setWrapMode(QOpenGLTexture::Repeat);
}

// fills buffers with data to draw a cube
void FoodGeometry::initVertex() {
  VertexData vertices[] = {
      // front
      {QVector3D(-0.5f, -0.5f, 0.5f), QVector2D(0.0f, 0.0f)},
      {QVector3D(0.5f, -0.5f, 0.5f), QVector2D(1.0f, 0.0f)},
      {QVector3D(0.5f, 0.5f, 0.5f), QVector2D(1.0f, 1.0f)},
      {QVector3D(-0.5f, 0.5f, 0.5f), QVector2D(0.0f, 1.0f)},

      // back
      {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(1.0f, 0.0f)},
      {QVector3D(0.5f, -0.5f, -0.5f), QVector2D(0.0f, 0.0f)},
      {QVector3D(0.5f, 0.5f, -0.5f), QVector2D(0.0f, 1.0f)},
      {QVector3D(-0.5f, 0.5f, -0.5f), QVector2D(1.0f, 1.0f)},

      // left
      {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.0f, 0.0f)},
      {QVector3D(-0.5f, -0.5f, 0.5f), QVector2D(1.0f, 0.0f)},
      {QVector3D(-0.5f, 0.5f, 0.5f), QVector2D(1.0f, 1.0f)},
      {QVector3D(-0.5f, 0.5f, -0.5f), QVector2D(0.0f, 1.0f)},

      // right
      {QVector3D(0.5f, -0.5f, 0.5f), QVector2D(0.0f, 0.0f)},
      {QVector3D(0.5f, -0.5f, -0.5f), QVector2D(1.0f, 0.0f)},
      {QVector3D(0.5f, 0.5f, -0.5f), QVector2D(1.0f, 1.0f)},
      {QVector3D(0.5f, 0.5f, 0.5f), QVector2D(0.0f, 1.0f)},

      // top
      {QVector3D(-0.5f, 0.5f, 0.5f), QVector2D(0.0f, 0.0f)},
      {QVector3D(0.5f, 0.5f, 0.5f), QVector2D(1.0f, 0.0f)},
      {QVector3D(0.5f, 0.5f, -0.5f), QVector2D(1.0f, 1.0f)},
      {QVector3D(-0.5f, 0.5f, -0.5f), QVector2D(0.0f, 1.0f)},

      // bottom
      {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.0f, 0.0f)},
      {QVector3D(0.5f, -0.5f, -0.5f), QVector2D(1.0f, 0.0f)},
      {QVector3D(0.5f, -0.5f, 0.5f), QVector2D(1.0f, 1.0f)},
      {QVector3D(-0.5f, -0.5f, 0.5f), QVector2D(0.0f, 1.0f)}};

  GLuint indices[] = {
      0,  1,  2,  2,  3,  0,  // front
      4,  5,  6,  6,  7,  4,  // back
      8,  9,  10, 10, 11, 8,  // left
      12, 13, 14, 14, 15, 12, // right
      16, 17, 18, 18, 19, 16, // top
      20, 21, 22, 22, 23, 20  // bottom
  };

  arrayBuffer.bind();
  arrayBuffer.allocate(vertices, 24 * sizeof(VertexData));

  indexBuffer.bind();
  indexBuffer.allocate(indices, 36 * sizeof(GLuint));
}
