#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct SpotLight {
    vec3  position;
    vec3  direction;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform SpotLight spotLight;

void main()
{
    vec3 lightDir = normalize(spotLight.position - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = spotLight.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    // specular
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewPos, reflectDir), 0.0), 32.0);
    vec3 specular = spotLight.specular * spec * texture(texture_specular1, TexCoords).rgb;

    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-spotLight.direction));
    float epsilon = (spotLight.cutOff - spotLight.outerCutOff);
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    // 光源衰减因子
    float distance    = length(spotLight.position - FragPos);
    float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));
    diffuse   *= attenuation;
    specular *= attenuation;

    FragColor = vec4(diffuse + specular, 1.0);
}