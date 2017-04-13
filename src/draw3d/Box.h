#ifndef BOX_H
#define BOX_H

#include <stdio.h>

#include "Drawable3d.h"

class Box : public Drawable3d
{
  public:
    Box();
    ~Box();
    virtual void Draw(float time);
    static void StaticInit();
  private:
    static const GLfloat *vertices;
    static GLuint VAO, VBO;
};

#endif
