//
// Created by jurek on 25.11.22.
//

#ifndef SNAKECGP_PLANEGEOMETRY_H
#define SNAKECGP_PLANEGEOMETRY_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class PlaneGeometry {
public:
    explicit PlaneGeometry(QMatrix4x4 model);

    virtual ~PlaneGeometry();

    void drawPlaneGeometry(QOpenGLShaderProgram *program,QMatrix4x4 projection);

private:
    void initPlaneGeometry();

    QOpenGLBuffer arrayBuffer;
    QOpenGLBuffer indexBuffer;

    QMatrix4x4 modelMatrix;
};


#endif //SNAKECGP_PLANEGEOMETRY_H
