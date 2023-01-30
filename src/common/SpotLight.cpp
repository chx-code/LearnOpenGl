//
// Created by cuihongxin on 2023/1/30.
//

#include "SpotLight.h"

SpotLight::SpotLight(const vec3 &position, const vec3 &direction, const float &cutOff, const float &outerCutOff,
                     const vec3 &ambient, const vec3 &diffuse, const vec3 &specular, const float &constant,
                     const float &linear, const float &quadratic) {
    this->position = position;
    this->direction = direction;
    this->cutOff = cutOff;
    this->outerCutOff = outerCutOff;

    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->setAttenuationParam(constant, linear, quadratic);
}

void SpotLight::setAttenuationParam(const float &constant, const float &linear, const float &quadratic) {
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}
