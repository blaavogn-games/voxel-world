#include "VoxelByteNote.h"

VoxelByteNote::VoxelByteNote(int x, int y, int z) : x(x), y(y), z(z){
  for(int xi = 0; xi < 32; ++xi)
    for(int yi = 0; yi < 32; ++yi)
      for(int zi = 0; zi < 32; ++zi)
        voxelBytes[xi][yi][zi] = nullptr;
}

void VoxelByteNote::Traverse(int x1, int y1, int z1, int x2, int y2, int z2, VoxelRenderer *voxelRenderer){
  for(int xi = x1; xi <= x2; xi += 32)
    for(int yi = y1; yi <= y2; yi += 32)
      for(int zi = z1; zi <= z2; zi += 32){
        VoxelByte* vb = voxelBytes[xi / 32][yi / 32][zi / 32];
        if(vb == nullptr){
          vb = new VoxelByteLeaf(xi,yi,zi);
          voxelBytes[xi / 32][yi / 32][zi / 32] = vb;
        }
        vb -> Traverse(xi, yi, zi, std::min(xi + 32, x2), std::min(yi + 32, y2), std::min(zi + 32, z2), voxelRenderer);
      }
}
