#include "Light.h"

Light::Light(const vec3 &position, const vec3 &ambient, const vec3 &diffuse, const vec3 &specular)
{
    this->position = position;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}