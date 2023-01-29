#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

//#include "Texture.h"

using namespace glm;
using namespace std;

class Material {
public:
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;

    Material(const vec3& ambient, const vec3& diffuse, const vec3& specular, float shininess);
};