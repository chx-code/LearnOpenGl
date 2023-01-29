#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

using namespace std;

class Texture
{
private:
    /* data */
    unsigned int mTexture;
    bool flip_vertically = true;
public:
    Texture(char const *filename, char const *filetype);
    Texture(const string filename, const string filetype);
    ~Texture();

    unsigned int getTexture();

    void BindTexture();
};

Texture::Texture(char const *filename, char const *filetype)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip_vertically);
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);

    // texture
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if (data) {
        if (!strcmp(filetype, (char*)"jpg")) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (!strcmp(filetype, (char*)"png")) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        
        // 当前绑定的纹理自动生成所有需要的多级渐远纹理
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture, file path: " << filename << std::endl;
    }
    
    // 生成了纹理和相应的多级渐远纹理后，释放图像的内存是一个很好的习惯
    stbi_image_free(data);
}

Texture::~Texture()
{
}

unsigned int Texture::getTexture() {
    return mTexture;
}

Texture::Texture(string filename, string filetype) {
    new (this) Texture(filename.c_str(), filetype.c_str());
}

void Texture::BindTexture() {

}
