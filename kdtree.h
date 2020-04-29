#ifndef KDTREE_H
#define KDTREE_H
#include "vertex.h"

class KDTree
{
public:
    KDTree(std::vector<Vertex> * points, int start, int end, int sortOn);
    KDTree(std::vector<Vertex> * points);
    void build(std::vector<Vertex> * points, int start, int end, int sortOn);
    void mergeSort(std::vector<Vertex> * points, int start, int end);
    void merge(std::vector<Vertex> * points, int left, int mid, int right);
    int getNextSortOn(int sortOn);
private:
    KDTree* __children[2];
    Vertex* __node;
    int __sortOn;
    int __start;
    int __end;

    Vertex * tempArray;
};

#endif // KDTREE_H
