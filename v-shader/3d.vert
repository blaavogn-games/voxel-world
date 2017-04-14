#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

uniform vec3 worldCoord;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

void main()
{
  vec3 worldPos = inPosition + worldCoord;
  gl_Position = projection * view * vec4(worldPos, 1.0);
  FragPos     = worldPos;
  Normal      = inNormal;
  TexCoord    = inTexCoord;
}
