#include "ShaderManager.h"

ShaderMap ShaderManager::map = ShaderMap(1);

Shader* ShaderManager::GetShader(const char *vertexPath, const char *fragmentPath){
  std::string vPath(vertexPath);
  std::string fPath(fragmentPath);
  std::string key = vPath + fPath;
  auto el = map.find(key);
  if (el == map.end()){
    Shader *shader = new Shader(vertexPath, fragmentPath);
    map.insert(std::make_pair(key, shader));
    return shader;
  }
  return (el->second);
}

void ShaderManager::SetCamera(Camera *camera, glm::vec3 *lightPosition){
  for (auto it = map.begin(); it != map.end(); ++it){
    it->second->UpdateCamera(camera, lightPosition);
  }
}
