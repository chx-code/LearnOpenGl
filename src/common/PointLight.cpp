#include "PointLight.h"

PointLight::PointLight(const vec3 &position, const vec3 &ambient, const vec3 &diffuse, const vec3 &specular,
                       const float &constant, const float &linear, const float &quadratic) {
    this->position = position;

    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->setAttenuationParam(constant, linear, quadratic);
}

void PointLight::setAttenuationParam(const float &Constant, const float &Linear, const float &Quadratic) {
    this->constant = Constant;
    this->linear = Linear;
    this->quadratic = Quadratic;
}
