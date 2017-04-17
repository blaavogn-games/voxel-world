#include "VoxelByteNote.h"

VoxelByteNote::VoxelByteNote(int x, int y, int z) {
  for(int xi = 0; xi < 32; ++xi)
    for(int yi = 0; yi < 32; ++yi)
      for(int zi = 0; zi < 32; ++zi)
        voxelBytes[xi][yi][zi] = nullptr;
}

void VoxelByteNote::Traverse(Camera camera){
  for(int xi = 0; xi < 32; ++xi){
    for(int yi = 0; yi < 32; ++yi){
      for(int zi = 0; zi < 32; ++zi){
          if(camera.WithinFrustum(glm::vec3(xi * 32, yi * 32, zi * 32),
                                  glm::vec3((xi + 1) * 32, (yi + 1)  * 32, (zi + 1) * 32))){
          VoxelByte* vb = voxelBytes[xi][yi][zi];
          if(vb == nullptr){
            vb = new VoxelByteLeaf(xi * 32,yi * 32,zi * 32);
            voxelBytes[xi][yi][zi] = vb;
          }
          vb -> Traverse(camera);
        }
      }
    }
  }
}
