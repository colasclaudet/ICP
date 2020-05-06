#include "pointcloud.h"

Pointcloud::Pointcloud()
{

}

Pointcloud::Pointcloud(QString filename)
{
    happly::PLYData data(filename.toStdString());
    std::vector<float> coordx = data.getElement("vertex").getProperty<float>("x");
    std::vector<float> coordy = data.getElement("vertex").getProperty<float>("y");
    std::vector<float> coordz = data.getElement("vertex").getProperty<float>("z");
    int mod = coordx.size()/this->maxPts;

    for(unsigned int i = 0; i<coordx.size(); i++)
    {
        float x = coordx.at(i);
        float y = coordy.at(i);
        float z = coordz.at(i);
        float dist = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
        if(dist>distmax)
        {
            distmax = dist;
        }
        if(dist<distmin)
        {
            distmin = dist;
        }
        if(mod > 0)
        {
            if(i%mod == 0)
            {
                this->points.push_back(Vertex(0.04,x,y,z));
            }
        }
        else
        {
            this->points.push_back(Vertex(0.04,x,y,z));
        }
    }
    /*for(unsigned int i = 0; i<coordx.size();i = i+4)
    {
        //Vertex v(0.5,coordx.at(i),coordy.at(i),coordz.at(i));
        //std::cout<<"coord x"<<coordx.at(i)<<std::endl;
        float x = coordx.at(i);
        float y = coordy.at(i);
        float z = coordz.at(i);
        this->points.push_back(Vertex(0.04,x,y,z));
    }*/
    //element vertex 471915
    //property float x
    //property float y
    //property float z

}

Pointcloud::Pointcloud(QString filename, int decimation)
{
    happly::PLYData data(filename.toStdString());
    std::vector<float> coordx = data.getElement("vertex").getProperty<float>("x");
    std::vector<float> coordy = data.getElement("vertex").getProperty<float>("y");
    std::vector<float> coordz = data.getElement("vertex").getProperty<float>("z");
    int mod = decimation;

    for(unsigned int i = 0; i<coordx.size(); i++)
    {
        float x = coordx.at(i);
        float y = coordy.at(i);
        float z = coordz.at(i);
        float dist = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
        if(dist>distmax)
        {
            distmax = dist;
        }
        if(dist<distmin)
        {
            distmin = dist;
        }
        if(mod > 0)
        {
            if(i%mod == 0)
            {
                this->points.push_back(Vertex(0.04,x,y,z));
            }
        }
        else
        {
            this->points.push_back(Vertex(0.04,x,y,z));
        }
    }
}

Pointcloud::Pointcloud(QString filename, QVector4D color)
{
    happly::PLYData data(filename.toStdString());
    std::vector<float> coordx = data.getElement("vertex").getProperty<float>("x");
    std::vector<float> coordy = data.getElement("vertex").getProperty<float>("y");
    std::vector<float> coordz = data.getElement("vertex").getProperty<float>("z");
    int mod = coordx.size()/this->maxPts;
    this->decimation = mod;
    for(unsigned int i = 0; i<coordx.size(); i = i + 1)
    {
        float x = coordx.at(i);
        float y = coordy.at(i);
        float z = coordz.at(i);
        float dist = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
        if(dist>distmax)
        {
            distmax = dist;
        }
        if(dist<distmin)
        {
            distmin = dist;
        }
        if(mod>0)
        {
            if(i%mod == 0)
            {
                Vertex v(0.04,x,y,z);
                v.setColor(color);
                this->points.push_back(v);
            }
        }
        else
        {
            this->points.push_back(Vertex(0.04,x,y,z));
        }
    }
}

Vertex Pointcloud::at(int i)
{
    return this->points.at(i);
}

QVector<Vertex> Pointcloud::getPoints() const
{
    return points;
}

void Pointcloud::setPoints(const QVector<Vertex> &value)
{
    points = value;
}

void Pointcloud::setColor(float r, float g, float b)
{
    color = QVector4D(r,g,b,0.5f);
}

float Pointcloud::getDistmin() const
{
    return distmin;
}

float Pointcloud::getDistmax() const
{
    return distmax;
}

QVector4D Pointcloud::getColor() const
{
    return color;
}

bool Pointcloud::save(std::string filename)
{
    // Suppose these hold your data
    std::vector<float> x_coord;
    std::vector<float> y_coord;
    std::vector<float> z_coord;

    for(int i = 0; i<this->points.size(); i++)
    {
        x_coord.push_back(this->points.at(i).getX());
        y_coord.push_back(this->points.at(i).getY());
        z_coord.push_back(this->points.at(i).getZ());
    }
    std::vector<std::vector<double>> elementB_listProp;

    // Create an empty object
    happly::PLYData plyOut;

    // Add elements
    plyOut.addElement("vertex", this->points.size());


    // Add properties to those elements
    plyOut.getElement("vertex").addProperty<float>("x", x_coord);
    plyOut.getElement("vertex").addProperty<float>("y", y_coord);
    plyOut.getElement("vertex").addProperty<float>("z", z_coord);

    // Write the object to file
    plyOut.write(filename+".ply", happly::DataFormat::Binary);
}

int Pointcloud::getDecimation() const
{
    return decimation;
}
