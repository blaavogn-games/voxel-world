#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <time.h>

#include "Shader.h"
#include "Window.h"

const GLuint WIDTH = 800, HEIGHT = 600;

int particleNum = 1 << 16;
int particleInfo = 5;
int curParticle = 0, lastParticle = 0;
size_t particleSize = sizeof(GLfloat) * particleInfo;

GLfloat* vertices;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursorCallback(GLFWwindow* window, double xPos, double yPos);
void mouseClickCallback(GLFWwindow* window, int button, int action, int mode);

int main() {
	GLFWwindow* window = Window::Init(WIDTH, HEIGHT, &keyCallback, &mouseClickCallback, &cursorCallback);
	if(!window){
		printf("Something went wrong with window initialization\n");
		exit(-1);
	}

  Shader shader("v-shader/part.shader","f-shader/blue.shader");

  vertices = new GLfloat[particleNum * particleInfo];
  for(int i = 0; i < particleNum * particleInfo; i++)
  	vertices[i] = -1000.0f;

  GLuint VBO, VAO, scale;
	scale = glGetUniformLocation(shader.Program, "scale");

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, particleSize * particleNum, vertices, GL_STREAM_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, particleSize, (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, particleSize, (GLvoid*) (2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, particleSize, (GLvoid*) (4 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
	while (!glfwWindowShouldClose(window))
	{
    glfwPollEvents();
		// glClearColor(0.2f,0.1f,0.4f,0.4f);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

    glUniform1f(scale, ((float) clock())/CLOCKS_PER_SEC);

    shader.Use();
    glBindVertexArray(VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
  	glBufferData(GL_ARRAY_BUFFER, particleSize * particleNum, vertices, GL_STREAM_DRAW);

		// if(lastParticle > curParticle){
		// 	glBufferSubData(GL_ARRAY_BUFFER, lastParticle, (particleNum - lastParticle) * particleSize, vertices);	
		// 	lastParticle = 0;
		// }
		// glBufferSubData(GL_ARRAY_BUFFER, lastParticle, (curParticle - lastParticle) * particleSize, vertices);
		// // glBufferSubData(GL_ARRAY_BUFFER, 0, (particleNum) * particleSize, vertices);
  // 	glBindBuffer(GL_ARRAY_BUFFER, 0);
  // 	lastParticle = curParticle;

    glDrawArrays(GL_POINTS, 0, particleNum);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
  return 0;
}

double tCord(double v, double max){
	return v * 2 / max - 1;
}

void addParticle(double xPos, double yPos){
	uint64_t i = particleInfo * curParticle;
	vertices[i] = tCord(xPos, WIDTH);
	vertices[i + 1] = tCord(HEIGHT - yPos, HEIGHT);
	vertices[i + 2] = ((float)(rand() % 200)) / 200.0f - 0.5f;
	vertices[i + 3] = ((float)(rand() % 200)) / 200.0f - 0.5f;
	vertices[i + 4] = ((float) clock())/CLOCKS_PER_SEC;
	curParticle = (curParticle + 1) % particleNum;
}

void cursorCallback(GLFWwindow* window, double xPos, double yPos)
{
	for(int i = 0; i < 30; i++)
		addParticle(xPos, yPos);
	// printf("F: %d\n", curParticle);
}


void mouseClickCallback(GLFWwindow* window, int button, int action, int mode)
{
	// double xpos, ypos;
	// glfwGetCursorPos(window, &xpos, &ypos);
	// int i = particleInfo * curParticle;
	// vertices[i] = tCord(xpos, WIDTH);
	// vertices[i + 1] = tCord(HEIGHT - ypos, HEIGHT);
	// curParticle = (curParticle + 1) % particleNum;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}