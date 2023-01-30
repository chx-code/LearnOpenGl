#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "Light.h"
#include "DirLight.h"
#include "PointLight.h"
#include "SpotLight.h"

using namespace glm;
using namespace std;

class Shader
{
public:
    // 程序ID
    unsigned int ID;

    // 构造器读取并构建着色器
    Shader(const string &vertexPath, const string &fragmentPath);
    // 使用/激活程序
    void use();
    // uniform工具函数
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, float valueX, float valueY) const;
    void setVec3(const std::string &name, const vec3 &value) const;
    void setVec3(const std::string &name, float valueX, float valueY, float valueZ) const;
    void setMat4(const std::string &name, mat4 &value) const;

    void setMaterial(const std::string &name, const Material& value) const;
    void setLight(const std::string &name, const Light& value) const;
    void setLight(const std::string &name, const DirLight& value) const;
    void setLight(const std::string &name, const PointLight& value) const;
    void setLight(const std::string &name, const SpotLight& value) const;
};

#endif