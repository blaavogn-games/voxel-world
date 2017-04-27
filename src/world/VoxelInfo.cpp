#include "VoxelInfo.h"

VoxelInfo::VoxelInfo (uint inTexture, Shader *inShader, bool inTransparent) {
  Texture   = inTexture;
  shader    = inShader;
  Transparent = inTransparent;
}
