#include "transformation.h"

Transformation::Transformation()
{

}

float *Transformation::getRotation() const
{
    return rotation;
}

void Transformation::setRotation(float *value)
{
    rotation = value;
}

float *Transformation::getTranslation() const
{
    return translation;
}

void Transformation::setTranslation(float *value)
{
    translation = value;
}
