//
// Created by cuihongxin on 2023/1/30.
//

#ifndef LEARNOPENGL_SPOTLIGHT_H
#define LEARNOPENGL_SPOTLIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;
using namespace std;

class SpotLight {
public:
    vec3  position;
    vec3  direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    SpotLight(const vec3& position, const vec3& direction, const float& cutOff, const float& outerCutOff, const vec3& ambient, const vec3& diffuse, const vec3& specular,
              const float& constant, const float& linear, const float& quadratic);

    void setAttenuationParam(const float& constant, const float& linear, const float& quadratic);
};

#endif //LEARNOPENGL_SPOTLIGHT_H
