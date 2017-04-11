#include "Box.h"
#include <cstring>

Box::Box() : Drawable3d(){
  shader = new Shader("v-shader/3d.vert","f-shader/circle.f");
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 24, vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 36, indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

}

Box::~Box(){
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  delete(shader);
}

void Box::Draw(Camera camera, float time){
  shader->Use();
  glBindVertexArray(VAO);
  glUniformMatrix4fv(shader->GetTransformLocation(), 1, GL_FALSE, glm::value_ptr(transform.GetMat()));
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
