#include "VoxelRenderer.h"

static const GLfloat temp_va[] = {
// Vertices                Normals                 Texture mapping
   0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
   0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
   0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     0.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
   0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
   0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
   0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
   0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
   0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
   0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
};
const GLfloat* VoxelRenderer::Vertices = temp_va;
static const GLuint temp_indices[] = {
  0,1,2,3,2,1,
  4,5,6,6,7,4,
  8,9,10,10,11,8,
  12,13,14,15,13,12,
  16,17,18,18,19,16,
  20,21,22,23,21,20
};
const GLuint* VoxelRenderer::Indices = temp_indices;

GLuint VoxelRenderer::VAO = -1;
GLuint VoxelRenderer::VBO = -1;
GLuint VoxelRenderer::EBO = -1;
Shader* VoxelRenderer::shader = nullptr;
std::vector<GLuint> VoxelRenderer::textures = std::vector<GLuint>();
int VoxelRenderer::c = 0;

void VoxelRenderer::StaticInit(){
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) * 6 * 4 * 8, Vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices) * 36, Indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  textures.push_back(ResourceManager::GetTexture("res/sun.png"));

  glBindVertexArray(VAO);
  glBindTexture(GL_TEXTURE_2D, textures[1]);
  shader = ShaderManager::GetShader("v-shader/3d.vert","f-shader/unlit.frag");
}

void VoxelRenderer::Draw(float x, float y, float z, char type){
  c++;
  shader->Use();
  glBindVertexArray(VAO);
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glUniform3f(shader->UniWorldCoord, x, y, z);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
