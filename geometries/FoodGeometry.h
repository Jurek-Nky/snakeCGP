//
// Created by jurek on 30.11.22.
//

#ifndef SNAKECGP_FOODGEOMETRY_H
#define SNAKECGP_FOODGEOMETRY_H

#include <QFile>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class FoodGeometry : QOpenGLFunctions {
public:
  explicit FoodGeometry(QMatrix4x4 model);

  virtual ~FoodGeometry();

  void drawFoodGeometry(QOpenGLShaderProgram *program, QMatrix4x4 projection);

private:
  QMatrix4x4 modelMatrix;

  void initFoodGeometry();

  void initVertex();

  void initTexture();

  QOpenGLBuffer arrayBuffer;
  QOpenGLBuffer indexBuffer;
  QOpenGLTexture *texture;

  QVector3D position;
};

#endif // SNAKECGP_FOODGEOMETRY_H
