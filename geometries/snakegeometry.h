#ifndef SNAKECGP_SNAKEGEOMETRY_H
#define SNAKECGP_SNAKEGEOMETRY_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>



class SnakeGeometry {
public:
    explicit SnakeGeometry(QMatrix4x4 model);

    virtual ~SnakeGeometry();

    void drawSnakeGeometry(QOpenGLShaderProgram *program, QMatrix4x4 projection);

    void drawSphereGeometry(QOpenGLShaderProgram *program, QMatrix4x4 projection);

    void addChild();

    void move(QMatrix4x4 parent);

private:
    QMatrix4x4 modelMatrix;

    void initSnakeGeometry();

    void initSphereGeometry(int latitudeBands, int longitudeBands);

    QOpenGLBuffer arrayBuffer;
    QOpenGLBuffer indexBuffer;

    SnakeGeometry *child = nullptr;
};


#endif //SNAKECGP_SNAKEGEOMETRY_H
