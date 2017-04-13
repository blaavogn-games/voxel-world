#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdio.h>

#include "Drawable.h"

class Circle : public Drawable
{
	private:
		GLfloat* vertices;
		Shader* shader;
		GLuint VAO, VBO;
		int segments;
	public:
		Circle(float cx, float cy, float rad, int num_segments);
		~Circle();
		void Draw(float time);
		void SetPosition(Vector2 position);
};

#endif
