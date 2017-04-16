#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

uniform vec3 worldCoord;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPosition;

out vec3 FragPos;
out vec2 TexCoord;
out float Diffuse;
out float Fog;

vec3 lightPosition = vec3(10,-10,10);

void main()
{
  vec3 worldPos = inPosition + worldCoord;
  gl_Position = projection * view * vec4(worldPos, 1.0);
  FragPos     = worldPos;
  TexCoord    = inTexCoord;

  vec3 lightDir = normalize(lightPosition - worldPos);
  Diffuse = max(dot(inNormal, lightDir), 0.0);
  float dist = length(worldPos - viewPosition); //Might be accesible through depthBuffer?
  Fog = dist * dist;
}
