#ifndef BOX_H
#define BOX_H

#include <stdio.h>

#include "Drawable3d.h"
#include "../Shader.h"

class Box : public Drawable3d
{
  private:
    const GLfloat vertices[12] = {
      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f
    };
    const GLuint indices[6] = {
      0,1,2,
      2,3,0
    };

    Shader* shader;
    GLuint VAO, VBO, EBO;
  public:
    Box(Vector3 pos);
    ~Box();
    virtual void Draw(float time);
    virtual void SetPosition(Vector3 pos);
    virtual void Move(Vector3);
};

#endif
