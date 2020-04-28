#include "vertex.h"

Vertex::Vertex(GLfloat size, float x, float y, float z)
{
    /*GLfloat vertices_particule[] = {
        x-size, y+size, z,
        x-size, y-size, z,
        x+size, y+size, z,
        x-size, y-size, z,
        x+size, y-size, z,
        x+size, y+size, z
    };*/

    this->x = x;
    this->y = y;
    this->z = z;
    this->size = size;

    this->position = QVector3D(x,y,z);
    GLfloat vertices_particule[] = {
        -size, size, 0.0f,
        -size, -size, 0.0f,
        size, size, 0.0f,
        -size, -size, 0.0f,
        size, -size, 0.0f,
        size, size, 0.0f
    };

    GLfloat texCoords_particule[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f
        };

    for (int i = 0; i < 6; ++i) {
        // coordonnées sommets
        for (int j = 0; j < 3; j++)
            vertData.append(vertices_particule[i*3+j]);
        // coordonnées texture
        for (int j = 0; j < 2; j++)
            vertData.append(texCoords_particule[i*2+j]);
    }
}

Vertex::Vertex()
{

}

void Vertex::setColor(float r,float g, float b, float a)
{
    this->color = QVector4D(r,g,b,a);
}

void Vertex::setColor(QVector4D _color)
{
    this->color = _color;
}

float Vertex::getZ() const
{
    return z;
}

GLfloat Vertex::getSize() const
{
    return size;
}

void Vertex::setSize(const GLfloat &value)
{
    size = value;
}

QVector4D Vertex::getColor() const
{
    return color;
}

float Vertex::getX() const
{
    return x;
}

float Vertex::getY() const
{
    return y;
}

void Vertex::display(QOpenGLShaderProgram *buffer)
{
    vbo.create();
    this->vbo.bind();
    this->vbo.allocate(vertData.constData(), vertData.count() * int(sizeof(GLfloat)));

    matrix.setToIdentity();
    matrix.translate(this->position);

    buffer->setUniformValue("modelMatrix", matrix);
    buffer->setUniformValue("particleSize", 1.0f);

    buffer->setUniformValue("color",this->color);

    buffer->setAttributeBuffer("in_position", GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    buffer->setAttributeBuffer("in_uv", GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));
    buffer->enableAttributeArray("in_position");
    buffer->enableAttributeArray("in_uv");


    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Vertex::anime(float dt, float ymin, float ymax)
{
    if(this->y>ymax-1)
    {
        this->up = false;
    }
    else if(this->y < ymin+1)
    {
        this->up = true;
    }

        if(this->up)
        {
            this->y += (rand()%100)/100.0;
        }
        else
        {
            this->y -= (rand()%100)/100.0;
        }

    this->position = QVector3D(this->x,this->y,this->z);
    float dist = sqrt(pow(ymin,2)+pow(ymax,2));
    float r = this->y/dist -0.15;
    float g = 1.0 - this->y/dist;
    //float b = sqrt(pow(r-g,2));
    float b = this->y/dist + 0.5;
    this->setColor(r,g,b,1.0);
}
