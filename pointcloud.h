#ifndef POINTCLOUD_H
#define POINTCLOUD_H
#include "vertex.h"
#include "happly.h"
class Pointcloud
{
public:
    Pointcloud();
    Pointcloud(QString filename);
    Pointcloud(QString filename, QVector4D color);
    Vertex at(int i);
    void push_back(Vertex v);
    QVector<Vertex> getPoints() const;
    void setPoints(const QVector<Vertex> &value);
    void setColor(float r,float g, float b);

    float getDistmin() const;

    float getDistmax() const;

    QVector4D getColor() const;

private:
    QVector<Vertex> points;
    float distmin = 1000000000000000000.0;
    float distmax = -1000000000000000000.0;
    QVector4D color = QVector4D(0.9f,1.0f,0.2f,0.5f);
};

#endif // POINTCLOUD_H
