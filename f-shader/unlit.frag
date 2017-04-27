#version 330 core

uniform sampler2D inTexture;

in vec2 TexCoord;

out vec4 color;

void main()
{
  color = texture(inTexture, TexCoord);
  color.w = 1.0f;
}
