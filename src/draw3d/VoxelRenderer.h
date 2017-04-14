#ifndef VOXELRENDERER_H
#define VOXELRENDERER_H

#include <stdio.h>
#include "Drawable3d.h"
#include "../shader/ShaderManager.h"

//This should possibly be static/singleton
class VoxelRenderer
{
  private:
    Shader *shader;
    static const GLfloat *vertices;
    static GLuint VAO, VBO, texture, texture2, texture3;
  public:
    VoxelRenderer();
    ~VoxelRenderer();
    virtual void Draw(float time, int x, int y, int z, char type);
    static void StaticInit();
};

#endif
