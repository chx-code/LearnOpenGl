#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

void main()
{
    if (fract(TexCoords.x) < 0.05)
        FragColor = vec4(0.04, 0.28, 0.26, 1.0);
    else if (fract(TexCoords.y) < 0.05)
        FragColor = vec4(0.04, 0.28, 0.26, 1.0);
    else
        FragColor = vec4(0.04, 0.08, 0.06, 0.5);
}