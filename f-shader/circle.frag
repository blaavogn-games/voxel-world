#version 330 core

uniform sampler2D inTexture;
uniform float noise;

in vec3 FragPos;
in vec2 TexCoord;
in float Diffuse;

out vec4 color;

float near = 1;
float far = 120;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
  //Abient Light
  float ambientStrength = 0.3f;
  vec3 ambient = ambientStrength * lightColor;

  vec4 tmpColor = texture(inTexture, TexCoord);
  float fog = LinearizeDepth(gl_FragCoord.z) / far;
  // color = vec4(vec3(fog * fog),1.0f);

  color = vec4((ambient + Diffuse), 1.0f) * tmpColor + (noise * 1 + fog) * vec4(0.3f,0.5f,0.5,1.0);
}
