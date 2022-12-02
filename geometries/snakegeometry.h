#ifndef SNAKECGP_SNAKEGEOMETRY_H
#define SNAKECGP_SNAKEGEOMETRY_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>


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

private:
    QMatrix4x4 modelMatrix;

    void initTexture();

    void initSnakeGeometry();

    void initVertex(int latitudeBands, int longitudeBands);

    QOpenGLBuffer arrayBuffer;
    QOpenGLBuffer indexBuffer;
    QOpenGLTexture *texture;

    SnakeGeometry *child = nullptr;


protected:
    QVector3D position;
};


#endif //SNAKECGP_SNAKEGEOMETRY_H
