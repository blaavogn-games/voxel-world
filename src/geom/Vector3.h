#ifndef VECTOR3
#define VECTOR3

#define GLEW_STATIC
#include <GL/glew.h>

#include <math.h>

class Vector3
{
	public:
		float x, y, z;
		Vector3(float x, float y, float z);
		// float Magnitude() const;
		// Vector2 Normalized();
    Vector3 Copy() const;
		// void Scale(float s);
  //   bool Contained(const Vector2&, const Vector2&) const;
		// GLfloat* operator>>(GLfloat*);
		Vector3 operator+(Vector3) const;
  //   Vector2 operator-(Vector2) const;
		// float operator*(Vector2) const; //dot-product
};

#endif
