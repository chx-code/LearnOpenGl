#include <Shader.h>

Shader::Shader(const string &vertexPath, const string &fragmentPath) {
    // 1. 从文件路径中获取顶点/片元着色器路径
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ, "
            << "vShaderFile path : " << vertexPath << ", fragmentPath : " << fragmentPath << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. 编译着色器
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // 顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // 打印编译错误（如果有的话）
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED, "
            << "infoLog : " << infoLog
            << "shader file path : " << vertexPath << std::endl;
    };

    // 片段着色器也类似
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // 打印编译错误（如果有的话）
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED, "
            << "infoLog : " << infoLog
            << "shader file path : " << fragmentPath << std::endl;
    };

    // 着色器程序
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // 打印连接错误（如果有的话）
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(ID);
}

// uniform工具函数
void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setVec2(const std::string &name, float valueX, float valueY) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), valueX, valueY);
}

void Shader::setVec3(const std::string &name,const vec3 &value) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec3(const std::string &name, float valueX, float valueY, float valueZ) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), valueX, valueY, valueZ);
}

void Shader::setMat4(const std::string &name, const mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value_ptr(value));
}

void Shader::setMaterial(const std::string &name, const Material &value) const
{
    this->setVec3(name + ".ambient",  value.ambient);
    this->setVec3(name + ".diffuse",  value.diffuse);
    this->setVec3(name + ".specular", value.specular);

    this->setFloat(name + ".shininess", value.shininess);
}

void Shader::setLight(const std::string &name, const Light &value) const
{
    this->setVec3(name + ".position", value.position);
    // this->setVec3("light.direction", value.direction);
    this->setVec3(name + ".ambient", value.ambient);
    this->setVec3(name + ".diffuse", value.diffuse);
    this->setVec3(name + ".specular", value.specular);
}

void Shader::setLight(const string &name, const DirLight &value) const {
    this->setVec3(name + ".direction", value.direction);
    this->setVec3(name + ".ambient", value.ambient);
    this->setVec3(name + ".diffuse", value.diffuse);
    this->setVec3(name + ".specular", value.specular);
}

void Shader::setLight(const string &name, const PointLight &value) const {
    this->setVec3(name + ".position", value.position);
    // this->setVec3("light.direction", value.direction);
    this->setVec3(name + ".ambient", value.ambient);
    this->setVec3(name + ".diffuse", value.diffuse);
    this->setVec3(name + ".specular", value.specular);

    this->setFloat(name + ".constant",  value.constant);
    this->setFloat(name + ".linear",    value.linear);
    this->setFloat(name + ".quadratic", value.quadratic);
}

void Shader::setLight(const string &name, const SpotLight &value) const {
    this->setVec3(name + ".position",  value.position);
    this->setVec3(name + ".direction", value.direction);
    this->setFloat(name + ".cutOff",   glm::cos(glm::radians(value.cutOff)));
    this->setFloat(name + ".outerCutOff",   glm::cos(glm::radians(value.outerCutOff)));

    this->setVec3(name + ".ambient", value.ambient);
    this->setVec3(name + ".diffuse", value.diffuse);
    this->setVec3(name + ".specular", value.specular);

    this->setFloat(name + ".constant",  value.constant);
    this->setFloat(name + ".linear",    value.linear);
    this->setFloat(name + ".quadratic", value.quadratic);
}
