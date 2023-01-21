#include "snakegeometry.h"
#include "vertexData.h"
#include <iostream>

SnakeGeometry::SnakeGeometry(QMatrix4x4 model)
    : indexBuffer(QOpenGLBuffer::IndexBuffer), texture(nullptr) {
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
  texture =
      new QOpenGLTexture(QImage(":/resources/textures/snake.png").mirrored());
  texture->setMinificationFilter(QOpenGLTexture::Nearest);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  texture->setWrapMode(QOpenGLTexture::Repeat);
}

void SnakeGeometry::initSnakeGeometry() {
  initTexture();
  initVertex(0.4, 1, 10, 20, true);
}

void SnakeGeometry::addChild() {
  if (child == nullptr) {
    child = new SnakeGeometry(modelMatrix);
    child->position = position;
    return;
  }
  child->addChild();
}

void SnakeGeometry::move(QVector3D pos) {
  if (child != nullptr) {
    child->move(position);
    child->orientation = orientation;
  }
  position = pos;
}

void SnakeGeometry::animate(float percentage, QVector3D direction,
                            QMatrix4x4 modelView) {
  if (child != nullptr) {
    child->animate(percentage, position - child->position, modelView);
  }

  modelView.translate(position - direction + direction * percentage);
  modelMatrix = modelView;
}

// create a solid cylinder with closed ends
void SnakeGeometry::initVertex(float radius, float height,
                               int verticalResolution, int horizontalResolution,
                               bool corner) {
  std::vector<VertexData> vertices;
  std::vector<GLushort> indices;

  float halfHeight = height / 2.0;
  float deltaAngle = 2 * M_PI / horizontalResolution;
  float deltaHeight = height / verticalResolution;

  for (int i = 0; i <= verticalResolution; ++i) {
    float y = halfHeight - i * deltaHeight;
    for (int j = 0; j <= horizontalResolution; ++j) {
      float angle = j * deltaAngle;
      float x = radius * std::cos(angle);
      float z = radius * std::sin(angle);
      VertexData v;
      v.position = QVector3D(x, y, z);
      v.normal = QVector3D(x, 0, y);
      v.uv = QVector2D(1.0f * j / horizontalResolution,
                       1.0f * i / verticalResolution);
      vertices.push_back(v);
    }
  }
  for (int i = 0; i < verticalResolution; ++i) {
    for (int j = 0; j < horizontalResolution; ++j) {
      int index = i * (horizontalResolution + 1) + j;
      indices.push_back(index);
      indices.push_back(index + 1);
      indices.push_back(index + horizontalResolution + 1);
      indices.push_back(index + horizontalResolution + 1);
      indices.push_back(index + 1);
      indices.push_back(index + horizontalResolution + 2);
    }
  }

  // add top and bottom
  int topIndex = vertices.size();
  int bottomIndex = vertices.size() + 1;
  VertexData top;
  top.position = QVector3D(0, 0, halfHeight);
  top.normal = QVector3D(0, 0, 1);
  top.uv = QVector2D(0.5, 0.5);
  vertices.push_back(top);
  VertexData bottom;
  bottom.position = QVector3D(0, 0, -halfHeight);
  bottom.normal = QVector3D(0, 0, -1);
  bottom.uv = QVector2D(0.5, 0.5);
  vertices.push_back(bottom);
  for (int i = 0; i < horizontalResolution; ++i) {
    indices.push_back(topIndex);
    indices.push_back(i + 1);
    indices.push_back(i);
  }
  for (int i = 0; i < horizontalResolution; ++i) {
    indices.push_back(bottomIndex);
    indices.push_back(bottomIndex - i - 2);
    indices.push_back(bottomIndex - i - 1);
  }

  // bind vertex array
  arrayBuffer.bind();
  arrayBuffer.allocate(vertices.data(), vertices.size() * sizeof(VertexData));

  // bind index array
  indexBuffer.bind();
  indexBuffer.allocate(indices.data(), indices.size() * sizeof(GLushort));
}

void SnakeGeometry::drawSnakeGeometry(QOpenGLShaderProgram *program,
                                      QMatrix4x4 projection) {
  QMatrix4x4 orientationMatrix = modelMatrix;
  if (orientation == X) {
    orientationMatrix.rotate(90, 0, 0, 1);
  }
  // if (corner != NO_CORNER) {
  //   initVertex(0.5, 1, 10, 20, false);
  // }
  program->setUniformValue("mvp_matrix", projection * orientationMatrix);

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

  // Tell OpenGL programmable pipeline how to locate vertex texture
  // coordinate data
  int texcoordLocation = program->attributeLocation("a_texcoord");
  program->enableAttributeArray(texcoordLocation);
  program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2,
                              sizeof(VertexData));

  texture->bind();
  program->setUniformValue("texture", 0);

  glDrawElements(GL_TRIANGLE_STRIP, indexBuffer.size(), GL_UNSIGNED_SHORT,
                 nullptr);

  if (child != nullptr) {
    child->drawSnakeGeometry(program, projection);
  }
}

// returns true if position == snakePosition otherwise it returns the call
// to its child
bool SnakeGeometry::checkCollision(QVector3D vector) {
  if (position == vector && !isHead) {
    return true;
  }
  if (child != nullptr) {
    return child->checkCollision(vector);
  }
  return false;
}

bool SnakeGeometry::checkFoodCollision(QVector3D food) {
  if (position == food) {
    return true;
  }
  return false;
}
