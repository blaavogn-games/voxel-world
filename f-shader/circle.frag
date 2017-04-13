#version 330 core

uniform vec3 viewPosition;
uniform sampler2D inTexture;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 color;

vec3 lightColor = vec3(1.0f, 0.1f, 1.0f);
vec3 objectColor = vec3(1.0f, 0.0f, 1.0f);
vec3 lightPosition = vec3(10,-10,10);

void main()
{
  vec3 norm = normalize(Normal);

  //Abient Light
  float ambientStrength = 0.1f;
  vec3 ambient = ambientStrength * lightColor;
  //Diffuse
  vec3 lightDir = normalize(lightPosition - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;
  //Specular
  float specularStrength = 0.75f;
  vec3 viewDir = normalize(viewPosition - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
  vec3 specular = specularStrength * spec * lightColor;

  vec4 tmpColor = texture(inTexture, TexCoord);
  color = vec4((ambient + diffuse + specular), 1.0f) * tmpColor;
}
