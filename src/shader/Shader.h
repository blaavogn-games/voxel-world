#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../draw3d/Camera.h"

class Shader
{
  private:
  public:
	  GLuint UniWorldCoord;
    GLuint UniView;
    GLuint UniProjection;
    GLuint UniViewPosition;
    GLuint UniLightPosition;
  	GLuint Program;
		Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
		~Shader();
    void Use();
    void UpdateCamera(Camera *camera, glm::vec3 *lightPosition);
};

#endif
