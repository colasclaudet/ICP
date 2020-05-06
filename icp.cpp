#include "icp.h"

ICP::ICP()
{

}

Pointcloud *ICP::icp(std::vector<Vertex *> &dynamicPointCloud, std::vector<Vertex *> &staticPointCloud)
{
    float rotationMatrix[9];
    float translation[3];

    std::vector<Vertex *> cpy;
    Vertex dynamicMid(0.04,0.0,0.0,0.0);
    Vertex staticMid(0.04,0.0,0.0,0.0);
    for(unsigned int i = 0; i< staticPointCloud.size();i++)
    {
        Vertex * v = new Vertex(0.04,staticPointCloud.at(i)->getX(),
                 staticPointCloud.at(i)->getY(),
                 staticPointCloud.at(i)->getZ());
        cpy.push_back(v);
    }
    KDTree * tree = new KDTree(staticPointCloud);
    size_t numDynamicPoints = dynamicPointCloud.size();

    //computeCloudMean(staticPointCloud, &staticMid);
    //computeCloudMean(dynamicPointCloud,&dynamicMid);
    computeCloudMean(staticPointCloud, &staticMid);
    computeCloudMean(dynamicPointCloud, &dynamicMid);

    clearTranslation(translation);
    clearRotation(rotationMatrix);

    const int maxIterations = 400; //400
    const int numRandomSamples = 400; //400
    const float eps = 1e-8;

    Vertex p(0.04,0.0,0.0,0.0);
    Vertex x(0.04,0.0,0.0,0.0);

    float cost = 1.0;
    std::srand(std::time(0));

    Vertex qd(0.04,0.0,0.0,0.0);
    Vertex qs(0.04,0.0,0.0,0.0);

    float U[9];
    float w[9];
    float sigma[3];
    float V[9];

    float** uSvd = new float*[3];
    float** vSvd = new float*[3];
    uSvd[0] = new float[3];
    uSvd[1] = new float[3];
    uSvd[2] = new float[3];

    vSvd[0] = new float[3];
    vSvd[1] = new float[3];
    vSvd[2] = new float[3];

    //boucle
    for (int iter = 0; iter < maxIterations && abs(cost) > eps; iter++)
    {
        cost = 0.0;

        //clearRotation(rotationMatrix);
        clearMatrix(U);
        clearMatrix(V);
        clearMatrix(w);
        //computeCloudMean(dynamicPointCloud, &dynamicMid);
        computeCloudMean(dynamicPointCloud, &dynamicMid);
        for (int i = 0; i < numRandomSamples; i++)
        {
            int randSample = std::rand() % dynamicPointCloud.size();
            // sample the dynamic point cloud
            p = *dynamicPointCloud.at(randSample);

            // get the closest point in the static point cloud
            tree->search(&p, &x);

            qd = Vertex(0.04,p.getX() - dynamicMid.getX(),
                        p.getY() - dynamicMid.getY(),
                        p.getZ() - dynamicMid.getZ());//p - dynamicMid
            qs = Vertex(0.04,x.getX() - staticMid.getX(),
                        x.getY() - staticMid.getY(),
                        x.getZ() - staticMid.getZ());//x - staticMid;

            outerProduct(&qs, &qd, w);
            addMatrix(w, U, U);

            cost += error(&x, &p, rotationMatrix, translation);
        }

        copyMatToUV(U, uSvd);
        dsvd(uSvd, 3, 3, sigma, vSvd);
        copyUVtoMat(uSvd, U);
        copyUVtoMat(vSvd, V);

        transpose(V);
        matrixMult(U, V, rotationMatrix);

        Vertex t(0.04,0.0, 0.0, 0.0);
        rotate(&dynamicMid, rotationMatrix, &t);
        translation[0] = staticMid.x - t.x;
        translation[1] = staticMid.y - t.y;
        translation[2] = staticMid.z - t.z;

        //update the point cloud
        for (unsigned int i = 0; i < dynamicPointCloud.size(); i++)
        {
            rotate(dynamicPointCloud.at(i), rotationMatrix, &p);
            translate(&p, translation, dynamicPointCloud.at(i));
            //MAYBE HERE
        }
    }

    cpy.clear();
    delete tree;

    delete[] uSvd[0];
    delete[] uSvd[1];
    delete[] uSvd[2];
    delete[] uSvd;

    delete[] vSvd[0];
    delete[] vSvd[1];
    delete[] vSvd[2];
    delete[] vSvd;

}

void ICP::clearTranslation(float* translation)
{
    translation[0] = 0.0;
    translation[1] = 0.0;
    translation[2] = 0.0;
}

void ICP::clearRotation(float* rotation)
{
    rotation[0] = 1.0;
    rotation[1] = 0.0;
    rotation[2] = 0.0;

    rotation[3] = 0.0;
    rotation[4] = 1.0;
    rotation[5] = 0.0;

    rotation[6] = 0.0;
    rotation[7] = 0.0;
    rotation[8] = 1.0;
}
