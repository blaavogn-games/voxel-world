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
  else if(inY < 128)
    for (int xi = 0; xi < 32; ++xi)
      for (int yi = 0; yi < 32; ++yi)
        for (int zi = 0; zi < 32; ++zi)
          voxels[xi][yi][zi] = 2;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
}


void VoxelByteLeaf::CalculateVisibleVoxels(){
  visibleVoxels.clear();

  auto root = VoxelByteNote::Root;
  for (int xi = 0; xi < 32; xi++)
    for (int yi = 0; yi < 32; yi++)
      for (int zi = 0; zi < 32; zi++)
        if (voxels[xi][yi][zi] != 0 && (
            root->At(xi+x-1,yi+y,zi+z) == 0 ||
            root->At(xi+x+1,yi+y,zi+z) == 0 ||
            root->At(xi+x,yi+y-1,zi+z) == 0 ||
            root->At(xi+x,yi+y+1,zi+z) == 0 ||
            root->At(xi+x,yi+y,zi+z-1) == 0 ||
            root->At(xi+x,yi+y,zi+z+1) == 0))
          visibleVoxels.push_back(glm::ivec3(xi,yi,zi));

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
      vertData[voxelIndex+vertIndex+7] = VoxelRenderer::Vertices[vertIndex+8];
    }
    voxelIndex = vi * 36;
    // Offseting EBO
    for(int i = 0; i < 36; i++)
      indData[voxelIndex+i] = VoxelRenderer::Indices[i] + vi * 24;
    vi++;
  }

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 192 * voxelsSize, vertData, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 36 * voxelsSize, indData, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  delete[] indData;
  delete[] vertData;
  auto shader = ShaderManager::GetShader("v-shader/3d.vert","f-shader/circle.frag");
  shader->Use();

}

void VoxelByteLeaf::Traverse(Camera camera){

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 36 * visibleVoxels.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  VoxelRenderer::c += visibleVoxels.size();
  // for(auto const& voxel: visibleVoxels)
  //   VoxelRenderer::Draw(0.0f, voxel.x + x, voxel.y + y, voxel.z + z, voxels[voxel.x][voxel.y][voxel.z]);
}

char VoxelByteLeaf::At(int xi, int yi, int zi){
  return voxels[xi - x][yi - y][zi - z];
}

