#ifndef SNAKECGP_SNAKEGEOMETRY_H
#define SNAKECGP_SNAKEGEOMETRY_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>


class SnakeGeometry : protected QOpenGLFunctions {
public:
    explicit SnakeGeometry(QMatrix4x4 model);

    virtual ~SnakeGeometry();

    void drawSnakeGeometry(QOpenGLShaderProgram *program, QMatrix4x4 projection);

    void addChild();

    void move(QMatrix4x4 parent);

private:
    QMatrix4x4 modelMatrix;

    void initTexture();

    void initSnakeGeometry();

    void initVertex(int latitudeBands, int longitudeBands);

    QOpenGLBuffer arrayBuffer;
    QOpenGLBuffer indexBuffer;
    QOpenGLTexture *texture;

    SnakeGeometry *child = nullptr;
};


#endif //SNAKECGP_SNAKEGEOMETRY_H
