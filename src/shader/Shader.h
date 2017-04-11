#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
  private:
	 GLuint transformLocation, viewLocation, projectionLocation;
  public:
  	GLuint Program;
		Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
		void Use();
    GLuint GetTransformLocation(){return transformLocation;};
    GLuint GetViewLocation(){return viewLocation;};
    GLuint GetProjectionLocation(){return projectionLocation;};
};

#endif
