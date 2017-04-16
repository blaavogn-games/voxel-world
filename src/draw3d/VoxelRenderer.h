#ifndef VOXELRENDERER_H
#define VOXELRENDERER_H

#include <stdio.h>
#include <vector>
#include "Drawable3d.h"
#include "../shader/ShaderManager.h"

//This should possibly be static/singleton
class VoxelRenderer
{
  private:
    Shader *shader;
    static const GLfloat *vertices;
    static GLuint VAO, VBO;
    static std::vector<GLuint> textures;
  public:
    VoxelRenderer();
    ~VoxelRenderer();
    virtual void Draw(float time, int x, int y, int z, char type);
    static void StaticInit();
};

#endif
