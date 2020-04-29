#include "icp.h"

ICP::ICP()
{

}

Pointcloud *ICP::icp(std::vector<Vertex> dynamicPointCloud, std::vector<Vertex> staticPointCloud)
{
    float rotationMatrix[9];
    float translation[3];

    std::vector<Vertex> cpy;
    Vertex dynamicMid(0.04,0.0,0.0,0.0);
    Vertex staticMid(0.04,0.0,0.0,0.0);
    for(unsigned int i = 0; i< staticPointCloud.size();i++)
    {
        Vertex v(0.04,staticPointCloud.at(i).getX(),
                 staticPointCloud.at(i).getY(),
                 staticPointCloud.at(i).getZ());
        cpy.push_back(v);
    }
    KDTree * tree = new KDTree(&staticPointCloud);
    //TODO
}
