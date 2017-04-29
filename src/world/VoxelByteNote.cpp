#include "VoxelByteNote.h"

VoxelByteNote::VoxelByteNote(int x, int y, int z) {
  this->x = x;
  this->y = y;
  this->z = z;
  for(int xi = 0; xi < 32; ++xi)
    for(int yi = 0; yi < 32; ++yi)
      for(int zi = 0; zi < 32; ++zi)
        voxelBytes[xi][yi][zi] = nullptr;
}

void VoxelByteNote::Traverse(Camera camera, bool trans){
  for (int xi = 0; xi < 32; ++xi){
    for (int yi = 0; yi < 32; ++yi){
      for (int zi = 0; zi < 32; ++zi){
        if (camera.WithinFrustum(glm::vec3(xi * 32, yi * 32, zi * 32),
                                glm::vec3((xi + 1) * 32, (yi + 1)  * 32, (zi + 1) * 32))){
          VoxelByte* vb = voxelBytes[xi][yi][zi];
          if (vb == nullptr)
          {
            vb = new VoxelByteLeaf(xi * 32,yi * 32,zi * 32);
            voxelBytes[xi][yi][zi] = vb;
            vb->CalculateVisibleVoxels();
            if(xi > 0  && voxelBytes[xi-1][yi][zi]!=nullptr)voxelBytes[xi-1][yi][zi]->CalculateVisibleVoxels();
            if(xi < 31 && voxelBytes[xi+1][yi][zi]!=nullptr)voxelBytes[xi+1][yi][zi]->CalculateVisibleVoxels();
            if(yi > 0  && voxelBytes[xi][yi-1][zi]!=nullptr)voxelBytes[xi][yi-1][zi]->CalculateVisibleVoxels();
            if(yi < 31 && voxelBytes[xi][yi+1][zi]!=nullptr)voxelBytes[xi][yi+1][zi]->CalculateVisibleVoxels();
            if(zi > 0  && voxelBytes[xi][yi][zi-1]!=nullptr)voxelBytes[xi][yi][zi-1]->CalculateVisibleVoxels();
            if(zi < 31 && voxelBytes[xi][yi][zi+1]!=nullptr)voxelBytes[xi][yi][zi+1]->CalculateVisibleVoxels();
          }
          vb->Traverse(camera, trans);
        }
      }
    }
  }
}

char VoxelByteNote::At(int xi, int yi, int zi){
  if(xi < 0 || yi < 0 || zi < 0)
    return 0;
  auto voxelByte = voxelBytes[(xi - x) / 32][(yi - y) / 32][(zi - z) / 32];
  if(voxelByte == nullptr)
    return 1;
  return voxelByte->At(xi,yi,zi);
}

char VoxelByteNote::At(glm::vec3 &pos){
  return At((int) (pos.x + 0.5),(int) (pos.y + 0.5),(int) (pos.z + 0.5));
}

void VoxelByteNote::Set(int xi, int yi, int zi, char v){
  if(xi < 0 || yi < 0 || zi < 0)
    return;
  auto voxelByte = voxelBytes[(xi - x) / 32][(yi - y) / 32][(zi - z) / 32];
  if(voxelByte == nullptr)
    return; //Perhaps spawn ??
  return voxelByte->Set(xi,yi,zi,v);
}

void VoxelByteNote::Set(glm::vec3 &pos, char v){
  return Set((int) (pos.x + 0.5),(int) (pos.y + 0.5),(int) (pos.z + 0.5), v);
}
