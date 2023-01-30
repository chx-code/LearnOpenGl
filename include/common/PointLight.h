/*
 * 点光源常用衰减方程参数：
 * 距离	常数项	一次项	二次项
 * 7	1.0     0.7 	1.8
 * 13	1.0	    0.35	0.44
 * 20	1.0	    0.22	0.20
 * 32	1.0	    0.14	0.07
 * 50	1.0	    0.09	0.032
 * 65	1.0	    0.07	0.017
 * 100	1.0	    0.045	0.0075
 * 160	1.0	    0.027	0.0028
 * 200	1.0	    0.022	0.0019
 * 325	1.0	    0.014	0.0007
 * 600	1.0	    0.007	0.0002
 * 3250	1.0	    0.0014	0.000007
 */
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;
using namespace std;

class PointLight {
public:
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    PointLight(const vec3& position, const vec3& ambient, const vec3& diffuse, const vec3& specular,
               const float& constant, const float& linear, const float& quadratic);

    void setAttenuationParam(const float& constant, const float& linear, const float& quadratic);
};
