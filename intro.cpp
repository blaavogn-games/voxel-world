#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdio.h>

#include "Shader.h"
#include "Window.h"

const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
	GLFWwindow* window = Window::Init(WIDTH, HEIGHT, &key_callback);
	if(!window){
		printf("Something went wrong with window initialization\n");
		exit(-1);
	}

  Shader ourShader("v-shader/red.shader","f-shader/simple.shader");

  GLfloat vertices[] = {
    // Positions         // Colors
    0.5f, -0.5f,   1.0f, 0.0f, 0.0f,  // Bottom Right
   -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  // Bottom Left
    0.0f,  0.5f,   0.0f, 0.0f, 1.0f   // Top 
  };

  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //sizeof ?!

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0); // Unbind VAO


	while (!glfwWindowShouldClose(window))
	{
    glfwPollEvents();
		glClearColor(0.8f,0.4f,0.4f,0.4f);
		glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    ourShader.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Swap the screen buffers
    glfwSwapBuffers(window);
	}

  // Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}