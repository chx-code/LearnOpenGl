//
// Created by cuihongxin on 2023/1/29.
//

#include "DirLight.h"

DirLight::DirLight(const vec3 &direction, const vec3 &ambient, const vec3 &diffuse, const vec3 &specular) {
    this->direction = direction;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}
