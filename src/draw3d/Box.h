#ifndef BOX_H
#define BOX_H

#include <stdio.h>

#include "Drawable3d.h"
#include "../Shader.h"

class Box : public Drawable3d
{
  private:
    const GLfloat vertices[24] = {
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,
       0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f, -0.5f, -0.5f
    };
    const GLuint indices[36] = {
      1,0,3, //Front
      3,2,1,
      2,3,7, //right
      7,6,2,
      1,2,6, //top
      6,5,1,
      1,5,4, //left
      4,0,1,
      0,4,3, //bottom
      3,4,7,
      5,6,7,
      7,4,5
    };

    Shader* shader;
    GLuint VAO, VBO, EBO;

  public:
    Box();
    ~Box();
    virtual void Draw(Camera camera, float time);
    // virtual void Move(Vector3);
};

#endif
