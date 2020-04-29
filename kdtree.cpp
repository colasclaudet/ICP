#include "kdtree.h"

KDTree::KDTree(std::vector<Vertex> * points, int start, int end, int sortOn)
{
    build(points, start, end, sortOn);
}

KDTree::KDTree(std::vector<Vertex> *points)
{
    tempArray = new Vertex[points->size()];
    build(points,0,points->size(),0);
    delete tempArray;
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
