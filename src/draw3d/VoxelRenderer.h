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
    static Shader *shader;
    static GLuint VAO, VBO, EBO;
    static std::vector<GLuint> textures;
  public:
    static const GLfloat *Vertices;
    static const GLuint *Indices;
    static int c;
    VoxelRenderer();
    ~VoxelRenderer();
    static void Draw(float time, int x, int y, int z, char type);
    static void StaticInit();
};

#endif
