#ifndef VOXELINFO_H
#define VOXELINFO_H

#include "../shader/Shader.h"

class VoxelInfo {
  public:
    uint Texture;
    Shader *shader;
    bool Transparent;
    VoxelInfo (uint inTexture, Shader *inShader, bool inTransparent);
};

#endif
