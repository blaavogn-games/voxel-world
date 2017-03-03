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
		float Magnitude() const;
		Vector2 Normalized();
    Vector2 Copy() const;
		void Scale(float s);
    bool Contained(const Vector2&, const Vector2&) const;
		GLfloat* operator>>(GLfloat*);
		Vector2 operator+(Vector2) const;
    Vector2 operator-(Vector2) const;
		float operator*(Vector2) const; //dot-product
};

#endif
