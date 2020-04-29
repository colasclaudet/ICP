#include "kdtree.h"

KDTree::KDTree(std::vector<Vertex> * points, int start, int end, int sortOn)
{
    build(points, start, end, sortOn);
}

KDTree::KDTree(std::vector<Vertex> *points)
{
    tempArray = new Vertex[points->size()];
    build(points,0,points->size(),0);
    //delete tempArray;
}

float KDTree::nodeX()
{
    return __node->getX();
}
float KDTree::nodeY()
{
    return __node->getY();
}
float KDTree::nodeZ()
{
    return __node->getZ();
}
float KDTree::split()
{
    float value = 0.0;
    if(__sortOn == 2)
    {
        value = __node->getZ();
    }
    else if(__sortOn == 1)
    {
        value = __node->getY();
    }
    else
    {
        value = __node->getX();
    }
    return value;
}
KDTree* KDTree::getChild(Vertex * searchPoint)
{
    float value = 0.0;
    if(__sortOn == 2)
    {
        value = searchPoint->getZ();
    }
    else if(__sortOn == 1)
    {
        value = searchPoint->getY();
    }
    else
    {
        value = searchPoint->getX();
    }
    if (value >= split())
    {
        return __children[1];
    }
    else
    {
        return __children[0];
    }
}
bool KDTree::isLeaf()
{
    if (__children[0] == nullptr && __children[1] == nullptr)
        return true;

    return false;
}

void KDTree::search(Vertex * p, Vertex* result)
{
    // get closets node
    KDTree* tree = this;
    while (!tree->isLeaf())
    {
        tree = tree->getChild(p);
    }
    result->x = tree->nodeX();
    result->y = tree->nodeY();
    result->z = tree->nodeZ();

    float radius = sqrt(pow(p->x - result->x, 2.0) + pow(p->y - result->y, 2.0) + pow(p->z - result->z, 2.0));

    radiusSearch(p, &radius, result);
}

void KDTree::radiusSearch(Vertex* p, float* radius, Vertex* result)
{
    if (isLeaf())
    {
        float d = sqrt(pow(__node->x - p->x, 2.0) + pow(__node->y - p->y, 2.0) + pow(__node->z - p->z, 2.0));
        if (d < *radius)
        {
            *radius = d;
            result->x = __node->x;
            result->y = __node->y;
            result->z = __node->z;
            return;
        }
    }
    else
    {
        float value_node = 0.0;
        float value_p = 0.0;
        if(__sortOn == 2)
        {
            value_node = __node->getZ();
            value_p = p->getZ();
        }
        else if(__sortOn == 1)
        {
            value_node = __node->getY();
            value_p = p->getY();
        }
        else
        {
            value_node = __node->getX();
            value_p = p->getX();
        }
        if (abs(value_node - value_p) < *radius)
        {
            __children[0]->radiusSearch(p, radius, result);
            __children[1]->radiusSearch(p, radius, result);
        }
        else
        {
            if (value_p >= value_node)
            {
                __children[1]->radiusSearch(p, radius, result);
            }
            else
            {
                __children[0]->radiusSearch(p, radius, result);
            }
        }
    }
}
void KDTree::build(std::vector<Vertex> *points, int start, int end, int sortOn)
{
    __children[0] = nullptr;
    __children[1] = nullptr;

    __node = nullptr;

    __sortOn = sortOn;
    __start = start;
    __end = end;

    if(end - start ==1)
    {
        __node = new Vertex(0.04,points->at(start).getX(),
                            points->at(start).getY(),
                            points->at(start).getZ());
        return;
    }
    //mergesort
    mergeSort(points,start,end);

    int numPoints = end - start;
    int mid = static_cast<int>(floor((numPoints)*0.5)) + start;

    __node = new Vertex(0.04,points->at(mid).getX(),points->at(mid).getY(),points->at(mid).getZ());

    int numPointsHigh =(end - mid);
    int numPointsLow = (mid - start);
    if(numPointsHigh > 0 )
    {
        __children[1] = new KDTree(points,mid,end,getNextSortOn(sortOn));//get next sort on
    }
    if (numPointsLow > 0)
    {
        __children[0] = new KDTree(points, start, mid, getNextSortOn(sortOn));
    }
}

void KDTree::mergeSort(std::vector<Vertex> *points, int start, int end)
{
    int mid;
    if(start>end)
    {
        mid = static_cast<int>(floor((end + start)*0.5));
        mergeSort(points,start,mid);
        mergeSort(points, mid+1 , end);

        merge(points, start,mid+1,end);
    }
}

void KDTree::merge(std::vector<Vertex> *points, int left, int mid, int right)
{
    int i, leftEnd, numElements, tempPos;

    leftEnd = mid;
    tempPos = 0;
    numElements = right - left;

    while (left < leftEnd && mid <= right)
    {
        float pleft = 0.0;
        float pmid = 0.0;
        if(__sortOn == 0)
        {
            pleft = points->at(left).getX();
            pmid = points->at(mid).getX();
        }
        else if(__sortOn == 1)
        {
            pleft = points->at(left).getY();
            pmid = points->at(mid).getY();
        }
        else if(__sortOn == 2)
        {
            pleft = points->at(left).getZ();
            pmid = points->at(mid).getZ();
        }

        if (pleft <= pmid)
        {
            tempArray[tempPos] = points->at(left);
            tempPos++;
            left++;
        }
        else
        {
            tempArray[tempPos] = points->at(mid);
            tempPos++;
            mid++;
        }
    }

    while (left < leftEnd)
    {
        tempArray[tempPos] = points->at(left);
        left++;
        tempPos++;
    }
    while (mid <= right)
    {
        tempArray[tempPos] = points->at(mid);
        mid++;
        tempPos++;
    }

    for (int i = tempPos - 1; i >= 0; i--)
    {
        points->at(right) = tempArray[i];
        right--;
    }
}

int KDTree::getNextSortOn(int sortOn)
{
    switch(sortOn)
    {
        case 0 :
            return 1;
        break;
        case 1 :
            return 2;
        break;
        case 2 :
            return 3;
        break;
    }
}
