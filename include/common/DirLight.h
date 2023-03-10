#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;
using namespace std;

class DirLight {
public:
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    DirLight(const vec3& direction, const vec3& ambient, const vec3& diffuse, const vec3& specular);
};
