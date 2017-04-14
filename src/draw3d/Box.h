#ifndef BOX_H
#define BOX_H

#include <stdio.h>
#include "Drawable3d.h"

class Box : public Drawable3d
{
  public:
    Box();
    ~Box();
    virtual void Draw(float time, int x, int y, int z);
    static void StaticInit();
  private:
    static const GLfloat *vertices;
    static GLuint VAO, VBO, texture, texture2, texture3;
};

#endif
