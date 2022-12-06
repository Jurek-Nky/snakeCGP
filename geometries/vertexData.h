#ifndef SNAKECGP_VERTEXDATA_H
#define SNAKECGP_VERTEXDATA_H

#include <QVector3D>

struct VertexData {
  QVector3D position;
  QVector2D uv;
  QVector3D normal;
};

#endif // SNAKECGP_VERTEXDATA_H
