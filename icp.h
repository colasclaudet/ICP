#ifndef ICP_H
#define ICP_H
#include "pointcloud.h"
#include "kdtree.h"
class ICP
{
public:
    ICP();
    Pointcloud * icp(std::vector<Vertex> dynamicPointCloud, std::vector<Vertex> staticPointCloud);
};

#endif // ICP_H
