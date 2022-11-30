#include "planegeometry.h"
#include "vertexData.h"


PlaneGeometry::PlaneGeometry(QMatrix4x4 model) {
    modelMatrix = model;
    initPlaneGeometry();
}

PlaneGeometry::~PlaneGeometry() {

}

void PlaneGeometry::initPlaneGeometry() {

    VertexData vertices[] = {
            {QVector3D(-0.5f, 0.0f, -0.5f), QVector2D(0.f, 0.0f)},
            {QVector3D(-0.5f, 0.0f, 0.5f),  QVector2D(0.f, 0.66f)},
            {QVector3D(0.5f, 0.0f, 0.5f),   QVector2D(0.5f, 0.66f)},
            {QVector3D(0.5f, 0.0f, -0.5f),  QVector2D(0.5f, 0.0f)},
    };
    GLushort indices[] = {
            0, 1, 2, 3
    };

    arrayBuffer.bind();
    arrayBuffer.allocate(vertices, 4 * sizeof(VertexData));

    indexBuffer.bind();
    indexBuffer.allocate(indices, 4 * sizeof(vertices));
}

void PlaneGeometry::drawPlaneGeometry(QOpenGLShaderProgram *program, QMatrix4x4 projection) {
    program->setUniformValue("mvp_matrix", projection * modelMatrix);

    arrayBuffer.bind();
    indexBuffer.bind();

    qintptr offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, nullptr);
}

