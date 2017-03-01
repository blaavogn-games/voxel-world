#version 330 core
in float normAge;

out vec4 color;

void main()
{
	float d = 1.3f * (0.5f - length(gl_PointCoord - vec2(0.5f,0.5f)));
	float rCom = 1.0f;
	if(normAge > 0.5f)
		rCom = 1.0f - (normAge - 0.5f) * 2;
  color = vec4(rCom, 1.0f - normAge, 0.5f - normAge * 0.5f, d);
} 