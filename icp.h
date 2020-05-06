#ifndef ICP_H
#define ICP_H
#include "pointcloud.h"
#include "kdtree.h"
#include "svd.h"
class ICP
{
public:
    ICP();
    Pointcloud * icp(std::vector<Vertex *> &dynamicPointCloud, std::vector<Vertex *> &staticPointCloud);

    void clearTranslation(float* translation);

    void clearRotation(float* rotation);

    inline Vertex computeCloudMean(std::vector<Vertex *> &cloud, Vertex * mean)
    {
        //Vertex mean(0.04,0.0,0.0,0.0);
        mean->x = 0.0;
        mean->y = 0.0;
        mean->z = 0.0;
        for (unsigned int i = 0; i < cloud.size(); i++)
        {
                mean->x += cloud.at(i)->x;
                mean->y += cloud.at(i)->y;
                mean->z += cloud.at(i)->z;
        }
        mean->x = mean->x / (float)cloud.size();
        mean->y = mean->y / (float)cloud.size();
        mean->z = mean->z / (float)cloud.size();
        return *mean;
    }
    inline void clearMatrix(float* mat)
    {
        mat[0] = 0.0;
        mat[1] = 0.0;
        mat[2] = 0.0;

        mat[3] = 0.0;
        mat[4] = 0.0;
        mat[5] = 0.0;

        mat[6] = 0.0;
        mat[7] = 0.0;
        mat[8] = 0.0;
    }
    inline void rotate(Vertex * p, float* rotationMatrix, Vertex * result)
    {
        result->x = p->getX() * rotationMatrix[0] + p->getY() * rotationMatrix[1] + p->getZ() * rotationMatrix[2];
        result->y = p->getX() * rotationMatrix[3] + p->getY() * rotationMatrix[4] + p->getZ() * rotationMatrix[5];
        result->z = p->getX() * rotationMatrix[6] + p->getY() * rotationMatrix[7] + p->getZ() * rotationMatrix[8];
    }

    inline void translate(Vertex * p, float* translationVector, Vertex * result)
    {
        result->x = p->getX() + translationVector[0];
        result->y = p->getY() + translationVector[1];
        result->z = p->getZ() + translationVector[2];
    }

    inline void outerProduct(Vertex * a, Vertex * b, float * mat)
    {
        mat[0] = a->getX() * b->getX();
        mat[1] = a->getX() * b->getY();
        mat[2] = a->getX() * b->getZ();

        mat[3] = a->getY() * b->getX();
        mat[4] = a->getY() * b->getY();
        mat[5] = a->getY() * b->getZ();

        mat[6] = a->getZ() * b->getX();
        mat[7] = a->getZ() * b->getY();
        mat[8] = a->getZ() * b->getZ();
    }

    inline void matrixMult(float* a, float* b, float* result)
    {
        result[0] = a[0] * b[0] + a[1] * b[3] + a[2] * b[6];
        result[1] = a[0] * b[1] + a[1] * b[4] + a[2] * b[7];
        result[2] = a[0] * b[2] + a[1] * b[5] + a[2] * b[8];

        result[3] = a[3] * b[0] + a[4] * b[3] + a[5] * b[6];
        result[4] = a[3] * b[1] + a[4] * b[4] + a[5] * b[7];
        result[5] = a[3] * b[2] + a[4] * b[5] + a[5] * b[8];

        result[6] = a[6] * b[0] + a[7] * b[3] + a[8] * b[6];
        result[7] = a[6] * b[1] + a[7] * b[4] + a[8] * b[7];
        result[8] = a[6] * b[2] + a[7] * b[5] + a[8] * b[8];
    }

    inline void transpose(float* a)
    {
        float temp;

        temp = a[1];
        a[1] = a[3];
        a[3] = temp;

        temp = a[2];
        a[2] = a[6];
        a[6] = temp;

        temp = a[5];
        a[5] = a[7];
        a[7] = temp;
    }

    inline void addMatrix(float* a, float* b, float* result)
    {
        result[0] = a[0] + b[0];
        result[1] = a[1] + b[1];
        result[2] = a[2] + b[2];

        result[3] = a[3] + b[3];
        result[4] = a[4] + b[4];
        result[5] = a[5] + b[5];

        result[6] = a[6] + b[6];
        result[7] = a[7] + b[7];
        result[8] = a[8] + b[8];
    }

    inline float error(Vertex * ps, Vertex * pt, float* r, float* t)
    {
        Vertex res(0.04,0.0,0.0,0.0);
        rotate(pt, r, &res);
        float err = pow(ps->getX() - res.getX() - t[0],2.0);
        err += pow(ps->getY() - res.getY() - t[1], 2.0);
        err += pow(ps->getZ() - res.getZ() - t[2], 2.0);
        return err;
    }

    inline void copyMatToUV(float* mat, float** result)
    {
        result[0][0] = mat[0];
        result[0][1] = mat[1];
        result[0][2] = mat[2];

        result[1][0] = mat[3];
        result[1][1] = mat[4];
        result[1][2] = mat[5];

        result[2][0] = mat[6];
        result[2][1] = mat[7];
        result[2][2] = mat[8];
    }

    inline void copyUVtoMat(float** mat, float* result)
    {
        result[0] = mat[0][0];
        result[1] = mat[0][1];
        result[2] = mat[0][2];

        result[3] = mat[1][0];
        result[4] = mat[1][1];
        result[5] = mat[1][2];

        result[6] = mat[2][0];
        result[7] = mat[2][1];
        result[8] = mat[2][2];
    }
};

#endif // ICP_H
