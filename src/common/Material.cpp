#include "Material.h"

Material::Material(const vec3 &ambient, const vec3 &diffuse, const vec3 &specular, float shininess)
{
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;

    this->shininess = shininess;
}
