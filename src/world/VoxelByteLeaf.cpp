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

void VoxelByteLeaf::Traverse(Camera camera){
  for (int xi = 0; xi < 32; xi++)
    for (int yi = 0; yi < 32; yi++)
      for (int zi = 0; zi < 32; zi++)
        if(yi < 31 && voxels[xi][yi + 1][zi] == 0)
        VoxelRenderer::Draw(0.0f, xi + x, yi + y, zi + z, voxels[xi][yi][zi]);

}
