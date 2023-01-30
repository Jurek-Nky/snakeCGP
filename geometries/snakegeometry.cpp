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
      new QOpenGLTexture(QImage(":/resources/textures/snake_tiger.png").mirrored());
  texture->setMinificationFilter(QOpenGLTexture::Nearest);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  texture->setWrapMode(QOpenGLTexture::Repeat);
}

void SnakeGeometry::initSnakeGeometry() {
  initTexture();
  initVertex(0.4, 1, 10, 20, false);
}

void SnakeGeometry::addChild() {
  if (child == nullptr) {
    child = new SnakeGeometry(modelMatrix);
    child->position = position;
    return;
  }
  child->addChild();
}

void SnakeGeometry::move(QVector3D pos, QMatrix4x4 modelView) {
  if (child != nullptr) {
    child->move(position, modelView);
    child->corner = corner;
    corner = NO_CORNER;
    child->orientation = orientation;
  }
  position = pos;
  modelView.translate(position);
  modelMatrix = modelView;
}

// create a solid cylinder with closed ends
void SnakeGeometry::initVertex(float radius, float height, int nStacks,
                               int nSlices, bool corner) {
  std::vector<VertexData> vertices;
  std::vector<GLushort> indices;
  if (!corner) {
    isCornerGeometry = false;
    float deltaAngle = 2 * M_PI / nSlices;
    float deltaHeight = height / nStacks;

    for (int i = 0; i <= nStacks; ++i) {
      float y = i * deltaHeight;
      for (int j = 0; j <= nSlices; ++j) {
        float angle = j * deltaAngle;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);
        VertexData v;
        v.position = QVector3D(x, y, z);
        v.uv = QVector2D(1.0f * j / nSlices, 1.0f * i / nStacks);
        v.normal = QVector3D(x, 0, z);
        vertices.push_back(v);
      }
    }
    for (int i = 0; i < nStacks; ++i) {
      for (int j = 0; j <= nSlices; ++j) {
        indices.push_back(i * (nSlices + 1) + j);
        indices.push_back((i + 1) * (nSlices + 1) + j);
      }
    }

    // add circle at the top
    VertexData v;
    v.position = QVector3D(0, height, 0);
    v.uv = QVector2D(0.5f, 0.5);
    v.normal = QVector3D(0, 1, 0);
    vertices.push_back(v);
    for (int i = 0; i <= nSlices; ++i) {
      indices.push_back(vertices.size() - 1);
      indices.push_back(vertices.size() - 3 - i);
    }

    // add circle at the bottom
    v.position = QVector3D(0, 0, 0);
    v.uv = QVector2D(0.5f, 1.0f);
    v.normal = QVector3D(0, -1, 0);
    vertices.push_back(v);
    for (int i = 0; i < nSlices; ++i) {
      indices.push_back(vertices.size() - 1);
      indices.push_back(i);
    }
  } else {
    isCornerGeometry = true;
    float deltaAngle = 2 * M_PI / nSlices;
    float deltaHeight = height / nStacks;

    for (int i = 0; i <= nStacks; ++i) {
      float y = i * deltaHeight;
      for (int j = 0; j <= nSlices; ++j) {
        float angle = j * deltaAngle;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);
        VertexData v;
        v.position = QVector3D(x, y, z);
        v.uv = QVector2D(1.0f * j / nSlices, 1.0f * i / nStacks);
        v.normal = QVector3D(x, 0, z);
        vertices.push_back(v);
      }
    }
    for (int i = 0; i < nStacks; ++i) {
      for (int j = 0; j <= nSlices; ++j) {
        indices.push_back(i * (nSlices + 1) + j);
        indices.push_back((i + 1) * (nSlices + 1) + j);
      }
    }

    // add circle at the top
    VertexData v;
    v.position = QVector3D(0, height, 0);
    v.uv = QVector2D(0.5f, 0.5);
    v.normal = QVector3D(0, 1, 0);
    vertices.push_back(v);
    for (int i = 0; i <= nSlices; ++i) {
      indices.push_back(vertices.size() - 1);
      indices.push_back(vertices.size() - 3 - i);
    }

    // add a second cylinder that is rotated by 90 degrees around the y-axis
    int indexOffset = vertices.size();
    for (int i = 0; i <= nStacks; ++i) {
      float x = i * deltaHeight;
      for (int j = 0; j <= nSlices; ++j) {
        float angle = j * deltaAngle;
        float y = radius * std::cos(angle);
        float z = radius * std::sin(angle);
        VertexData v;
        v.position = QVector3D(x, y, z);
        v.uv = QVector2D(1.0f * j / nSlices, 1.0f * i / nStacks);
        v.normal = QVector3D(x, 0, z);
        vertices.push_back(v);
      }
    }
    indices.push_back(indexOffset);
    for (int i = 0; i < nStacks; ++i) {
      for (int j = 0; j <= nSlices; ++j) {
        indices.push_back(i * (nSlices + 1) + j + indexOffset);
        indices.push_back((i + 1) * (nSlices + 1) + j + indexOffset);
      }
    }

    // add circle at the top
    v.position = QVector3D(height, 0, 0);
    v.uv = QVector2D(0.5f, 0.5);
    v.normal = QVector3D(0, 1, 0);
    vertices.push_back(v);
    for (int i = 0; i <= nSlices; ++i) {
      indices.push_back(vertices.size() - 1);
      indices.push_back(vertices.size() - 3 - i);
    }

    // add a sphere at the center
    indexOffset = vertices.size();
    int latitudeBands = 20;
    int longitudeBands = 20;

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
        indices.push_back(first + indexOffset);
        indices.push_back(second + indexOffset);
        indices.push_back(first + 1 + indexOffset);

        indices.push_back(second + indexOffset);
        indices.push_back(second + 1 + indexOffset);
        indices.push_back(first + 1 + indexOffset);
      }
    }
  }

  // Transfer vertex data to VBO 0
  arrayBuffer.bind();
  arrayBuffer.allocate(vertices.data(), vertices.size() * sizeof(VertexData));

  // Transfer index data to VBO 1
  indexBuffer.bind();
  indexBuffer.allocate(indices.data(), indices.size() * sizeof(GLushort));
}

void SnakeGeometry::drawSnakeGeometry(QOpenGLShaderProgram *program,
                                      QMatrix4x4 projection) {
  if (corner != NO_CORNER && !isCornerGeometry) {
    initVertex(0.4, 1, 10, 20, true);
  } else if (corner == NO_CORNER && isCornerGeometry) {
    initVertex(0.4, 1, 10, 20, false);
  }
  QMatrix4x4 orientationMatrix = modelMatrix;
  switch (corner) {
  case TOP_LEFT:
    orientationMatrix.rotate(90, 0, 0, 1);
    break;
  case TOP_RIGHT:
    break;
  case BOTTOM_RIGHT:
    orientationMatrix.rotate(270, 0, 0, 1);
    break;
  case BOTTOM_LEFT:
    orientationMatrix.rotate(180, 0, 0, 1);
    break;
  case NO_CORNER:
    if (orientation == X) {
      orientationMatrix.rotate(90, 0, 0, 1);
    }
    break;
  }
  // if (corner != NO_CORNER) {
  //   initVertex(0.5, 1, 10, 20, false);
  // }
  program->setUniformValue("model_matrix", modelMatrix);
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

  offset += sizeof(QVector2D);

  int normalLocation = program ->attributeLocation("a_normal");
  program->enableAttributeArray(normalLocation);
  program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3,
                              sizeof(VertexData));

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
void SnakeGeometry::newOrientation(Orientation orientation, Directions oldDir,
                                   Directions newDir) {
  if (orientation == this->orientation) {
    return;
  }

  this->orientation = orientation;
  if (child != nullptr && isHead) {
    int x;
    switch (oldDir) {
    case UP:
      x = newDir == LEFT ? BOTTOM_LEFT : BOTTOM_RIGHT;
      break;
    case DOWN:
      x = newDir == LEFT ? TOP_LEFT : TOP_RIGHT;
      break;
    case LEFT:
      x = newDir == UP ? TOP_RIGHT : BOTTOM_RIGHT;
      break;
    case RIGHT:
      x = newDir == UP ? TOP_LEFT : BOTTOM_LEFT;
      break;
    }

    corner = Corner(x);
  }
}
