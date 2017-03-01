#include "Line.h"

Line::Line(Vector2 start, Vector2 end) : position((start.x + end.x) / 2, (start.y + end.y) / 2){
	shader = new Shader("v-shader/circle.v","f-shader/circle.f");
	end >> (start >> vertices);
	start.x += 0.3f;
  glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 2, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

Line::~Line(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete(vertices);
	delete(shader);
}

void Line::Draw(float time){
	shader->Use();
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 2, vertices, GL_STATIC_DRAW);
  glDrawArrays(GL_LINE_LOOP, 0, 2);
  glBindVertexArray(0);
}

void Line::SetPosition(Vector2 newPosition){
	Vector2 delta = newPosition - position;
	position = newPosition;
	for(int i = 0; i < 2 * 2; i+=2){
		vertices[i]   += delta.x;
		vertices[i+1] += delta.y;
	}
}
