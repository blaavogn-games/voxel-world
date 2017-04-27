#ifndef VOXELTYPES_H
#define VOXELTYPES_H

#include <stdio.h>
#include <vector>
#include "../shader/ShaderManager.h"
#include "../io/ResourceManager.h"
#include "VoxelInfo.h"

class VoxelTypes
{
  public:
    static int Nums;
    static std::vector<VoxelInfo> Infos;
    static void StaticInit();
};

#endif
