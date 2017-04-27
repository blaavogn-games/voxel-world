#include "VoxelByteLeaf.h"

VoxelByteLeaf::VoxelByteLeaf(int inX, int inY, int inZ) : VoxelByte(), x(inX), y(inY), z(inZ){
  for (int xi = 0; xi < 32; ++xi)
    for (int yi = 0; yi < 32; ++yi)
      for (int zi = 0; zi < 32; ++zi)
        voxels[xi][yi][zi] = 0;

  if (inY == 128)
    for (int yi = 0; yi < 16; ++yi)
      for (int xi = yi; xi < 32 - yi; ++xi)
        for (int zi = yi; zi < 32 - yi; ++zi)
          voxels[xi][yi][zi] = (yi == 0) ? 2 : 1;
  else if (inY < 128)
    for (int xi = 0; xi < 32; ++xi)
      for (int yi = 0; yi < 32; ++yi)
        for (int zi = 0; zi < 32; ++zi)
          voxels[xi][yi][zi] = (inY+yi < 128 && inY+yi >= 125) ? 2 : 1;

  VAO = new GLuint[VoxelTypes::Infos.size()];
  VBO = new GLuint[VoxelTypes::Infos.size()];
  EBO = new GLuint[VoxelTypes::Infos.size()];
  sizes = new int[VoxelTypes::Infos.size()];

  glGenVertexArrays(VoxelTypes::Infos.size(), VAO);
  glGenBuffers(VoxelTypes::Infos.size(), VBO);
  glGenBuffers(VoxelTypes::Infos.size(), EBO);
}

VoxelByteLeaf::~VoxelByteLeaf(){
  // ToDo: Should store changes and delete buffers
}

void VoxelByteLeaf::CalculateVisibleVoxels(){
  int typesSize = VoxelTypes::Infos.size();
  std::vector<glm::ivec3> visibleVoxelsVector[typesSize];
  for (int types = 0; types < typesSize; types++)
  {
    auto visibleVoxels = visibleVoxelsVector[types];
    for (int xi = 0; xi < 32; xi++)
      for (int yi = 0; yi < 32; yi++)
        for (int zi = 0; zi < 32; zi++)
          if (voxels[xi][yi][zi] != 0 && voxels[xi][yi][zi] == types && (
              VoxelTypes::Infos[VoxelByteNote::Root->At(xi+x-1,yi+y,zi+z)].Transparent ||
              VoxelTypes::Infos[VoxelByteNote::Root->At(xi+x+1,yi+y,zi+z)].Transparent ||
              VoxelTypes::Infos[VoxelByteNote::Root->At(xi+x,yi+y-1,zi+z)].Transparent ||
              VoxelTypes::Infos[VoxelByteNote::Root->At(xi+x,yi+y+1,zi+z)].Transparent ||
              VoxelTypes::Infos[VoxelByteNote::Root->At(xi+x,yi+y,zi+z-1)].Transparent ||
              VoxelTypes::Infos[VoxelByteNote::Root->At(xi+x,yi+y,zi+z+1)].Transparent)) {
            visibleVoxels.push_back(glm::ivec3(xi,yi,zi));
          }

    int voxelsSize = visibleVoxels.size();
    GLfloat *vertData = new GLfloat[192 * voxelsSize];
    GLuint *indData = new GLuint[36 * voxelsSize];
    int vi = 0;
    for(auto const& voxel: visibleVoxels){
      int voxelIndex = vi * 192;
      for(int i = 0; i < 4 * 6; i++){
        int vertIndex = i * 8;
        // Offseting position
        vertData[voxelIndex+vertIndex+0] = VoxelRenderer::Vertices[vertIndex+0]+voxel.x+x;
        vertData[voxelIndex+vertIndex+1] = VoxelRenderer::Vertices[vertIndex+1]+voxel.y+y;
        vertData[voxelIndex+vertIndex+2] = VoxelRenderer::Vertices[vertIndex+2]+voxel.z+z;
        // Keeping normals and uv-map
        vertData[voxelIndex+vertIndex+3] = VoxelRenderer::Vertices[vertIndex+3];
        vertData[voxelIndex+vertIndex+4] = VoxelRenderer::Vertices[vertIndex+4];
        vertData[voxelIndex+vertIndex+5] = VoxelRenderer::Vertices[vertIndex+5];
        vertData[voxelIndex+vertIndex+6] = VoxelRenderer::Vertices[vertIndex+6];
        vertData[voxelIndex+vertIndex+7] = VoxelRenderer::Vertices[vertIndex+7];
      }
      voxelIndex = vi * 36;
      // Offseting EBO
      for(int i = 0; i < 36; i++)
        indData[voxelIndex+i] = VoxelRenderer::Indices[i] + vi * 24;
      vi++;
    }
    glBindVertexArray(VAO[types]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[types]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 192 * voxelsSize, vertData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[types]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 36 * voxelsSize, indData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    sizes[types] = voxelsSize;
    delete[] indData;
    delete[] vertData;
  }
}

void VoxelByteLeaf::Traverse(Camera camera, bool transparent){
  for (uint types = 0; types < VoxelTypes::Infos.size(); types++){
    if (sizes[types] == 0 || (!transparent && types == 2) || (transparent && types != 2)){
      continue;
    }

    VoxelRenderer::c += sizes[types];
    auto voxelInfo = VoxelTypes::Infos[types];
    glBindVertexArray(VAO[types]);
    voxelInfo.shader->Use();
    glUniform3f(voxelInfo.shader->UniWorldCoord, 0, 0, 0);
    glBindTexture(GL_TEXTURE_2D, voxelInfo.Texture);
    glDrawElements(GL_TRIANGLES, 36*sizes[types], GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
}

char VoxelByteLeaf::At(int xi, int yi, int zi){
  return voxels[xi - x][yi - y][zi - z];
}
