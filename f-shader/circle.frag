#version 330 core

in vec3 Normal;
in vec3 FragPos;

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
  color = vec4((ambient + diffuse) * objectColor, 1.0f);
}
