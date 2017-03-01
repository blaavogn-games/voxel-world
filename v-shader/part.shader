#version 330 core
uniform float time;
layout (location = 0) in vec2 position; 
layout (location = 1) in vec2 vel; 
layout (location = 2) in float birth; 

out float normAge;

void main()
{
	float age = (time - birth) / 1000.0f;
	normAge = age / 5.0;
	gl_Position = vec4(position.x + vel.x * age, position.y + vel.y * age, 0.0f, 1.0f);
	
	if(age < 5.0f)
  	gl_PointSize = 3.0 + age * 5.0f;
  else
  	gl_PointSize = 0.0f;
}