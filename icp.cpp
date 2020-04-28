#include "icp.h"

ICP::ICP()
{

}

Pointcloud *ICP::icp(std::vector<Vertex> dynamicPointCloud, std::vector<Vertex> staticPointCloud)
{
    float rotationMatrix[9];
    float translation[3];

    std::vector<Vertex> cpy;
}
