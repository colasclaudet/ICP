#ifndef ICP2_H
#define ICP2_H
#include "transformation.h"
#include "statistics.h"

class ICP2
{
public:
    ICP2();

protected:
    bool compute_projection();
    bool compute_distance(Statistics &stat, const double tolerance = 0.0);
    bool compute_best_fit(Transformation &transfo);
    bool apply_transformation(Transformation & transfo);
};

#endif // ICP2_H
