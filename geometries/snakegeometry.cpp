#include "snakegeometry.h"
#include "vertexData.h"

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
      new QOpenGLTexture(QImage(":/resources/textures/snake.jpg").mirrored());
  texture->setMinificationFilter(QOpenGLTexture::Nearest);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  texture->setWrapMode(QOpenGLTexture::Repeat);
}

void SnakeGeometry::initSnakeGeometry() {
  initTexture();
  initVertex(50, 50);
}

void SnakeGeometry::addChild() {
  if (child == nullptr) {
    child = new SnakeGeometry(modelMatrix);
    child->position = position;
    return;
  }
  child->addChild();
}

void SnakeGeometry::move(QMatrix4x4 parent, QVector3D pos) {
  if (child != nullptr) {
    child->move(modelMatrix, position);
    child->position = position;
  }
  position = pos;
  modelMatrix = parent;
}

// this function fills vertices and indices vectors with data to draw a sphere
// with the given vertical and horizontal resolution
void SnakeGeometry::initVertex(int latitudeBands, int longitudeBands) {
  std::vector<VertexData> vertices;
  std::vector<GLushort> indices;
  float radius = 0.5f;
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

      vertices.push_back(
          {QVector3D(x * radius, y * radius, z * radius), QVector2D(u, v)});
    }
  }

  for (int latNumber = 0; latNumber < latitudeBands; latNumber++) {
    for (int longNumber = 0; longNumber < longitudeBands; longNumber++) {
      int first = (latNumber * (longitudeBands + 1)) + longNumber;
      int second = first + longitudeBands + 1;
      indices.push_back(first);
      indices.push_back(second);
      indices.push_back(first + 1);

      indices.push_back(second);
      indices.push_back(second + 1);
      indices.push_back(first + 1);
    }
  }

  // bind vertices to array buffer
  arrayBuffer.bind();
  arrayBuffer.allocate(vertices.data(), vertices.size() * sizeof(VertexData));

  // bind indices to index buffer
  indexBuffer.bind();
  indexBuffer.allocate(indices.data(), indices.size() * sizeof(GLushort));
}

void SnakeGeometry::drawSnakeGeometry(QOpenGLShaderProgram *program,
                                      QMatrix4x4 projection) {
  program->setUniformValue("mvp_matrix", projection * modelMatrix);

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

  texture->bind();
  program->setUniformValue("texture", 0);

  glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_SHORT, nullptr);

  if (child != nullptr) {
    child->drawSnakeGeometry(program, projection);
  }
}

// returns true if position == snakePosition otherwise it returns the call to
// its child
bool SnakeGeometry::checkCollision(QVector3D vector) {
  if (position == vector and !isHead) {
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
