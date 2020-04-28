#ifndef VERTICES_H
#define VERTICES_H

#include "vertex.h"
class Vertices
{
public:
    Vertices(GLfloat size,QList<Vertex> vertices);
    void display(QOpenGLShaderProgram * buffer);
    void anime(float dt, float ymin, float ymax);
private:
    QList<Vertex> listVertices;
};

#endif // VERTICES_H
