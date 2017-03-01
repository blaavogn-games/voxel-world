#ifndef LINE_H
#define LINE_H

#include <stdio.h>

#include "Drawable.h"
#include "../Shader.h"

class Line : public Drawable
{
	private:
		Vector2 position;
		GLfloat* vertices = new GLfloat[6];
		Shader* shader;
		GLuint VAO, VBO;
	public:
		Line(Vector2 start, Vector2 end);
		~Line();
		void Draw(float time);
		void SetPosition(Vector2 position);
};
  
#endif