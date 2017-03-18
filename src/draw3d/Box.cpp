#include "Box.h"
#include <cstring>

Box::Box(Vector3 pos) : Drawable3d(pos.x, pos.y, pos.z){
  shader = new Shader("v-shader/3d.v","f-shader/circle.f");
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 12, vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 6, indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
}

Box::~Box(){
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  delete(shader);
}

void Box::Draw(float time){
  shader->Use();
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Box::SetPosition(Vector3 pos){
}

void Box::Move(Vector3 movement){
  position = movement + position;
}
