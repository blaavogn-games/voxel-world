#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

void main()
{
  gl_Position = projection * view * transform * vec4(inPosition, 1.0);
  FragPos     = vec3(transform * vec4(inPosition, 1.0));
  Normal      = mat3(transpose(inverse(transform))) * inNormal;
  TexCoord    = inTexCoord;
}
