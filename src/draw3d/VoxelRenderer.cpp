#include "VoxelRenderer.h"
static const GLfloat temp_va[] = {
// Vertices                Normals                 Texture mapping
   0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
   0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f, 1.0f,
   0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f, 0.0f,

  -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
   0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     0.0f, 0.0f,

  -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,     0.0f, 0.0f,

   0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
   0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
   0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
   0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f, 0.0f,

  -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
   0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
   0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     0.0f, 0.0f,

  -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
   0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
   0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
   0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
};

const GLfloat* VoxelRenderer::vertices = temp_va;
GLuint VoxelRenderer::VAO = -1;
GLuint VoxelRenderer::VBO = -1;
Shader* VoxelRenderer::shader = nullptr;
std::vector<GLuint> VoxelRenderer::textures = std::vector<GLuint>();
int VoxelRenderer::c = 0;

void VoxelRenderer::StaticInit(){
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 216, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);

  textures.push_back(ResourceManager::GetTexture("res/grass.png"));
  textures.push_back(ResourceManager::GetTexture("res/grass.png"));
  textures.push_back(ResourceManager::GetTexture("res/water.png"));

  shader = ShaderManager::GetShader("v-shader/3d.vert","f-shader/circle.frag");
  shader->Use();

  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);
}

void VoxelRenderer::Draw(float time, int x, int y, int z, char type){
  if(type==0)
    return;
  c++;
  glBindTexture(GL_TEXTURE_2D, textures[type]);
  glUniform3f(shader->transformLocation, x, y, z);
  glUniform1f(shader->noiseLocation, ((float)(rand() % 100)) / 6000.0f);
  glDrawArrays(GL_TRIANGLES, 0, 36);
}
