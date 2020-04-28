#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class Vertex
{
public:
    Vertex(GLfloat size, float x, float y, float z);
    Vertex();
    void display(QOpenGLShaderProgram * buffer);
    void anime(float dt, float ymin, float ymax);
    void setColor(float r,float g, float b, float a);
    void setColor(QVector4D _color);

    float x,y,z;

    float getX() const;

    float getY() const;

    float getZ() const;

    GLfloat getSize() const;
    void setSize(const GLfloat &value);

    QVector4D getColor() const;

private:

    QOpenGLBuffer vbo;
    QVector4D color = QVector4D(0.9f,1.0f,0.2f,0.5f);
    QVector3D position = QVector3D(0.0,0.0,0.0);
    QMatrix4x4 matrix;
    QVector<GLfloat> vertData;
    GLfloat size;
    bool up = true;
};

#endif // VERTEX_H
