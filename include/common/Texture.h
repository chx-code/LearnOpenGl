#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

using namespace std;

class Texture
{
private:
    /* data */
    unsigned int mTexture;
    string type;
    string path;

    bool flip_vertically = true;
public:
    Texture(char const *filename, bool gamma = false);
    Texture(const string filename, bool gamma = false);

    unsigned int getTexture();
    unsigned int getTextureID();

    const string &getType() const;
    void setType(const string &type);

    const string &getPath() const;
};

