#include "ResourceManager.h"

TextureMap ResourceManager::map = TextureMap(1);

GLuint ResourceManager::GetTexture(const char *path){
  std::string key(path);
  auto el = map.find(key);

  if (el == map.end()){
    GLuint texture;
    int w, h;
    unsigned char* image = SOIL_load_image(path, &w, &h, 0, SOIL_LOAD_RGBA);
    printf("%d, %d\n", w, h);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    map.insert(std::make_pair(key, texture));
    return texture;
  }
  return (el->second);
}
