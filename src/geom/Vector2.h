#ifndef VECTOR2
#define VECTOR2

#define GLEW_STATIC
#include <GL/glew.h>

#include <math.h>

class Vector2
{
	public:
		float x, y;
		Vector2(float x, float y);
		float Magnitude();
		Vector2 Normalized();
		Vector2 Copy();
		GLfloat* operator>>(GLfloat*);
		Vector2 operator+(Vector2);
		Vector2 operator-(Vector2);
};
  
#endif