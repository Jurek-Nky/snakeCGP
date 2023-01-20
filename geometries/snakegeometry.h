#ifndef SNAKECGP_SNAKEGEOMETRY_H
#define SNAKECGP_SNAKEGEOMETRY_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <vector>

enum Corner { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, NO_CORNER };
enum Orientation { X, Y };

class SnakeGeometry : protected QOpenGLFunctions {
public:
  explicit SnakeGeometry(QMatrix4x4);

  virtual ~SnakeGeometry();

  void drawSnakeGeometry(QOpenGLShaderProgram *, QMatrix4x4);

  void addChild();

  void move(QMatrix4x4, QVector3D);

  bool checkCollision(QVector3D);

  bool checkFoodCollision(QVector3D);

  bool isHead = false;

  bool isTail = false;

  Orientation orientation;

private:
  QMatrix4x4 modelMatrix;

  void initTexture();

  void initSnakeGeometry();

  void initVertex(float radius, float height, int verticalResolution,
                  int horizontalResolution, bool corner);

  QOpenGLBuffer arrayBuffer;

  QOpenGLBuffer indexBuffer;

  QOpenGLTexture *texture;

  SnakeGeometry *child = nullptr;


  Corner corner;

protected:
  QVector3D position;
};

#endif // SNAKECGP_SNAKEGEOMETRY_H
