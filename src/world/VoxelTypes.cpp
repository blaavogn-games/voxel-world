#include "VoxelTypes.h"

std::vector<VoxelInfo> VoxelTypes::Infos = std::vector<VoxelInfo>();
int VoxelTypes::Nums = 0;

void VoxelTypes::StaticInit(){
  glActiveTexture(GL_TEXTURE0);

  Shader *diffuse = ShaderManager::GetShader("v-shader/3d.vert","f-shader/diffuse.frag");
  Shader *water = ShaderManager::GetShader("v-shader/3d.vert","f-shader/diffuse.frag");
  GLuint res = ResourceManager::GetTexture("res/grass.png");
  Infos.push_back(VoxelInfo(res, diffuse, true));
  Infos.push_back(VoxelInfo(res, diffuse, false));
  res = ResourceManager::GetTexture("res/water3.png");
  Infos.push_back(VoxelInfo(res, water, true));
  Nums = Infos.size();
}
