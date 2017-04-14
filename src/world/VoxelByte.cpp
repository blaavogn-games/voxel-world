#include "VoxelByte.h"

VoxelByte::VoxelByte(int x, int y, int z) : x(x), y(y), z(z){
  for(int i = 0; i < 32; i++)
    for(int j = 0; i < 32; i++)
      voxels[i * 32 + j] = (i + j) % 3;
}

void VoxelByte::Traverse(int x1, int y1, int z1, int x2, int y2, int z2, VoxelRenderer *voxelRenderer){
  for(int xi = x1; xi <= x2; xi++)
    for(int yi = y1; yi <= y2; yi++)
      for(int zi = 0; zi <= z2; zi++)
        voxelRenderer->Draw(0.0f, xi, yi, zi, voxels[xi * 32 + zi]);
}
