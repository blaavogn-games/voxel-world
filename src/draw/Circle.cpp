#include <stdio.h>
#include <math.h>
#include "Circle.h"

Circle::Circle(float cx, float cy, float rad, int num_segments) : Drawable(cx, cy){
	shader = new Shader("v-shader/circle.v","f-shader/circle.f");
	segments = num_segments;
	vertices = new GLfloat[num_segments * 2];
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);
	float s = sinf(theta);
	float t;
	float x = rad;
	float y = 0;

	for(int ii = 0; ii < num_segments * 2; ii+=2)
	{
		vertices[ii] = x + cx;
		vertices[ii + 1] = y + cy;
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}

  glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * segments, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

Circle::~Circle(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete(vertices);
	delete(shader);
}

void Circle::Draw(float time){
	shader->Use();
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * segments, vertices, GL_STATIC_DRAW);
  glDrawArrays(GL_LINE_LOOP, 0, segments);
  glBindVertexArray(0);
}

void Circle::SetPosition(Vector2 newPosition){
  Vector2 delta = newPosition - position;
  position = newPosition;
  for(int i = 0; i < segments * 2; i+=2){
    vertices[i]   += delta.x;
    vertices[i+1] += delta.y;
  }
}
