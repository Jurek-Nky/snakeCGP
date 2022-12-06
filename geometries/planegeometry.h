#ifndef SNAKECGP_PLANEGEOMETRY_H
#define SNAKECGP_PLANEGEOMETRY_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class PlaneGeometry : protected QOpenGLFunctions {
public:
  explicit PlaneGeometry(QMatrix4x4 model);

  virtual ~PlaneGeometry();

  void drawPlaneGeometry(QOpenGLShaderProgram *program, QMatrix4x4 projection);

private:
  void initPlaneGeometry();

  void initTexture();

  void initVertex();

  QOpenGLBuffer arrayBuffer;

  QOpenGLTexture *texture;

  QMatrix4x4 modelMatrix;
};

#endif // SNAKECGP_PLANEGEOMETRY_H
