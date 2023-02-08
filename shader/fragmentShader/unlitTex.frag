#version 330 core
struct Material {
    sampler2D diffuse1;
    sampler2D specular1;
    sampler2D reflect1;
};

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform Material material;
uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
    vec3 result = texture(material.diffuse1, TexCoords).rgb + texture(material.specular1, TexCoords).rgb + texture(material.reflect1, TexCoords).rgb;
    FragColor = vec4(result, 1.0);
}