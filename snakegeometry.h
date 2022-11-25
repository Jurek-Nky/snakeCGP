//
// Created by jurek on 25.11.22.
//

#ifndef SNAKECGP_SNAKEGEOMETRY_H
#define SNAKECGP_SNAKEGEOMETRY_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class SnakeGeometry {
public:
    SnakeGeometry();

    virtual ~SnakeGeometry();

    void drawSnakeGeometry(QOpenGLShaderProgram *program);

    QVector2D getPosition();

    void setPosition(QVector2D pos);

private:
    void initSnakeGeometry();

    QOpenGLBuffer arrayBuffer;
    QOpenGLBuffer indexBuffer;


    QVector2D position = QVector2D(0.0, 0.0);
};


#endif //SNAKECGP_SNAKEGEOMETRY_H
