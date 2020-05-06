#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H


class Transformation
{
public:
    Transformation();
    float *getRotation() const;
    void setRotation(float *value);

    float *getTranslation() const;
    void setTranslation(float *value);

private :
    float * rotation;
    float * translation;
};

#endif // TRANSFORMATION_H
