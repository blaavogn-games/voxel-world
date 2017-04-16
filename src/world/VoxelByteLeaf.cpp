#include "VoxelByteLeaf.h"

VoxelByteLeaf::VoxelByteLeaf(int inX, int inY, int inZ) : VoxelByte(), x(inX), y(inY), z(inZ){
  for (int xi = 0; xi < 32; ++xi)
    for (int yi = 0; yi < 32; ++yi)
      for (int zi = 0; zi < 32; ++zi)
        voxels[xi][yi][zi] = 0;

  if (inY == 0){
    for (int yi = 0; yi < 32; ++yi)
      for (int xi = yi; xi < 32 - yi; ++xi)
        for (int zi = yi; zi < 32 - yi; ++zi)
          voxels[xi][yi][zi] = (yi == 0) ? 2 : 1;
  } else if(inY < 0){
    for (int xi = 0; xi < 32; ++xi)
      for (int yi = 0; yi < 32; ++yi)
        for (int zi = 0; zi < 32; ++zi)
          voxels[xi][yi][zi] = 1;
  }
}

void VoxelByteLeaf::Traverse(int x1, int y1, int z1, int x2, int y2, int z2, VoxelRenderer *voxelRenderer){
  for (int xi = x1; xi < x2; xi++)
    for (int yi = y1; yi < y2; yi++)
      for (int zi = z1; zi < z2; zi++)
        if (yi + 1 >= y2 || voxels[xi - x][yi - y + 1][zi - z] == 0)
          voxelRenderer->Draw(0.0f, xi, yi, zi, voxels[xi - x][yi - y][zi - z]);
}
