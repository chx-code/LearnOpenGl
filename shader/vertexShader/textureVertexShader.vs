#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

out vec3 ourColor;
out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
    ourColor = aColor;
    TexCoords = aTexCoords;
}