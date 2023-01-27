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

  texture->bind();
  program->setUniformValue("texture", 0);

  // Tell OpenGL which VBOs to use
  arrayBuffer.bind();
  indexBuffer.bind();

  // Offset for position
  quintptr offset = 0;

  // Tell OpenGL programmable pipeline how to locate vertex position data
  int vertexLocation = program->attributeLocation("a_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3,
                              sizeof(VertexData));

  // Offset for texture coordinate
  offset += sizeof(QVector3D);

  // Tell OpenGL programmable pipeline how to locate vertex texture coordinate
  // data
  int texcoordLocation = program->attributeLocation("a_texcoord");
  program->enableAttributeArray(texcoordLocation);
  program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2,
                              sizeof(VertexData));

  glDrawElements(GL_TRIANGLE_STRIP, indexBuffer.size(), GL_UNSIGNED_SHORT,
                 nullptr);
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
  float radius = 0.5f;
  int latitudeBands = 30;
  int longitudeBands = 30;
  std::vector<VertexData> vertices;
  std::vector<GLushort> indices;

  for (int latNumber = 0; latNumber <= latitudeBands; latNumber++) {
    float theta = latNumber * M_PI / latitudeBands;
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);

    for (int longNumber = 0; longNumber <= longitudeBands; longNumber++) {
      float phi = longNumber * 2 * M_PI / longitudeBands;
      float sinPhi = sin(phi);
      float cosPhi = cos(phi);

      float x = cosPhi * sinTheta;
      float y = cosTheta;
      float z = sinPhi * sinTheta;

      float u = 1 - (longNumber / (float)longitudeBands);
      float v = 1 - (latNumber / (float)latitudeBands);

      VertexData vertex;
      vertex.position = QVector3D(x * radius, y * radius, z * radius);
      vertex.uv = QVector2D(u, v);
      vertex.normal = QVector3D(x, y, z);
      vertices.push_back(vertex);
    }
  }
  // push back indices
  for (int latNumber = 0; latNumber < latitudeBands; latNumber++) {
    for (int longNumber = 0; longNumber <= longitudeBands; longNumber++) {
      indices.push_back(latNumber * (longitudeBands + 1) + longNumber);
      indices.push_back((latNumber + 1) * (longitudeBands + 1) + longNumber);
    }
  }

  // Transfer vertex data to VBO 0
  arrayBuffer.bind();
  arrayBuffer.allocate(vertices.data(), vertices.size() * sizeof(VertexData));

  // Transfer index data to VBO 1
  indexBuffer.bind();
  indexBuffer.allocate(indices.data(), indices.size() * sizeof(GLushort));
}
