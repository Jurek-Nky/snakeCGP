//
// Created by jurek on 30.11.22.
//

#ifndef SNAKECGP_SKYBOX_H
#define SNAKECGP_SKYBOX_H

#include <QFile>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class Skybox : QOpenGLFunctions {
public:
  explicit Skybox(QMatrix4x4 model);

  virtual ~Skybox();

  void drawSkybox(QOpenGLShaderProgram *program, QMatrix4x4 projection);

private:
  QMatrix4x4 modelMatrix;

  void initSkybox();

  void initVertex();

  void initTexture();

  QOpenGLBuffer arrayBuffer;
  QOpenGLBuffer indexBuffer;
  QOpenGLTexture *texture;

  QVector3D position;
};

#endif // SNAKECGP_SKYBOX_H
