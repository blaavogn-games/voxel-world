#version 330 core

uniform sampler2D inTexture;
uniform float noise;

in vec3 FragPos;
in vec2 TexCoord;
in float Diffuse;
in float Fog;

out vec4 color;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

void main()
{
  //Abient Light
  float ambientStrength = 0.3f;
  vec3 ambient = ambientStrength * lightColor;

  vec4 tmpColor = texture(inTexture, TexCoord);
  // color = tmpColor;
  color = vec4((ambient + Diffuse), 1.0f) * tmpColor + (Fog * .00012 + (Fog * noise * .00000004)) * vec4(0.3f,0.5f,0.5,1.0);
}
