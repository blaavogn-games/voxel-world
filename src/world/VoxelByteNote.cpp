#include "VoxelByteNote.h"

VoxelByteNote::VoxelByteNote(int x, int y, int z) {
  for(int xi = 0; xi < 32; ++xi)
    for(int yi = 0; yi < 32; ++yi)
      for(int zi = 0; zi < 32; ++zi)
        voxelBytes[xi][yi][zi] = nullptr;
}

void VoxelByteNote::Traverse(int x1, int y1, int z1, int x2, int y2, int z2, VoxelRenderer *voxelRenderer){
  for(int xi = x1/32; xi*32 <= x2; ++xi){
    for(int yi = 0; yi*32 <= y2; ++yi){
      for(int zi = z1/32; zi*32 <= z2; ++zi){
        VoxelByte* vb = voxelBytes[xi][yi][zi];

        if(vb == nullptr){
          vb = new VoxelByteLeaf(xi * 32,yi * 32,zi * 32);
          voxelBytes[xi][yi][zi] = vb;
        }
        int minX = std::max(xi * 32, x1);
        int minY = std::max(yi * 32, y1);
        int minZ = std::max(zi * 32, z1);
        int maxX = std::min((xi + 1) * 32, x2);
        int maxY = std::min((yi + 1) * 32, y2);
        int maxZ = std::min((zi + 1) * 32, z2);

        vb -> Traverse(minX, minY, minZ, maxX, maxY, maxZ, voxelRenderer);
      }
    }
  }
}
