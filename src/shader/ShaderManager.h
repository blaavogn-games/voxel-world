#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>
#include <unordered_map>
#include "Shader.h"
#include "../draw3d/Camera.h"

typedef std::unordered_map <std::string, Shader*> ShaderMap;

class ShaderManager
{
  private:
    static ShaderMap map;
  public:
    static Shader* GetShader(const char *vertexPath, const char *fragmentPath);
    static void SetCamera(Camera *camera);
};

#endif
