/*
 * Created by cuihongxin on 2023/1/31.
 */

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char *filename, bool gamma) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip_vertically);
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);

    // texture
    glGenTextures(1, &mTexture);

    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else
            throw std::runtime_error("ERROR empty stack");

        glBindTexture(GL_TEXTURE_2D, mTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        this->path = filename;
    } else {
        std::cout << "Failed to load texture, file path: " << filename << std::endl;
    }

    // 生成了纹理和相应的多级渐远纹理后，释放图像的内存是一个很好的习惯
    stbi_image_free(data);
}

Texture::Texture(const string filename, bool gamma) {
    new (this) Texture(filename.c_str(), gamma);
}

unsigned int Texture::getTexture() {
    return mTexture;
}

unsigned int Texture::getTextureID() {
    return mTexture;
}

const string &Texture::getType() const {
    return type;
}

void Texture::setType(const string &type) {
    Texture::type = type;
}

const string &Texture::getPath() const {
    return path;
}
