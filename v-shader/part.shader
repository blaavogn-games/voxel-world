#version 330 core
uniform float scale;
layout (location = 0) in vec2 position; 
layout (location = 1) in vec2 vel; 
layout (location = 2) in float time; 

out float age;

void main()
{
	age = (scale - time) / 5.0f;
	gl_Position = vec4(position.x + vel.x * age * 3, position.y + vel.y * age * 3, 0.0f, 1.0f);
	
	if(scale - time < 5.0f)
  	gl_PointSize = 3.0 + age * 20.0f;
  else
  	gl_PointSize = 0.0f;
}