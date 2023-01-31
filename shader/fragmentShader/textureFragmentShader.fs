#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
    // FragColor = texture(texture1, TexCoords);
    // FragColor = texture(texture1, TexCoords) * vec4(ourColor, 1.0);
    FragColor = mix(texture(texture1, TexCoords), texture(texture2, TexCoords), 0.2);
    // FragColor = mix(texture(texture1, TexCoords), texture(texture2, TexCoords), mixValue);
    // FragColor = mix(texture(texture1, TexCoords), texture(texture2, vec2(TexCoords.x, -TexCoords.y)), 0.2);
}