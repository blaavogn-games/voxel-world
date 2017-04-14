#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <unordered_map>
#include <SOIL.h>

typedef std::unordered_map <std::string, GLuint> TextureMap;

class ResourceManager
{
  private:
    static TextureMap map;
  public:
    static GLuint GetTexture(const char *path);
};

#endif
