#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "src/Timer.h"
#include "src/Shader.h"
#include "src/draw/Circle.h"
#include "src/draw/Line.h"
#include "src/Window.h"

const GLuint WIDTH = 600, HEIGHT = 600;
Timer timer;
Drawable* circle;
Drawable* colLine;
Drawable* line1;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursorCallback(GLFWwindow* window, double xPos, double yPos);
void mouseClickCallback(GLFWwindow* window, int button, int action, int mode);
void DrawCircle(float cx, float cy, float r, int num_segments);

int main() {
	GLFWwindow* window = Window::Init(WIDTH, HEIGHT, &keyCallback, &mouseClickCallback, &cursorCallback);
	if(!window){
		printf("Something went wrong with window initialization\n");
		exit(-1);
	}

	circle = new Circle(0.0f, 0.0f, 0.2f, 20);
	colLine = new Line(Vector2(0.8f,0.8f), Vector2(-0.4f,-0.4f));
	line1 = new Line(Vector2(0.8f,0.8f), Vector2(-0.4f,-0.4f));

	while (!glfwWindowShouldClose(window))
	{
    glfwPollEvents();
		if(timer.IsPaused())
			continue;
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
    circle->Draw(timer.GetMs());
    colLine->Draw(timer.GetMs());
    line1->Draw(timer.GetMs());
		glfwSwapBuffers(window);
	}
	delete(circle);
	glfwTerminate();
  return 0;
}

double tCord(double v, double max){
	return v * 2 / max - 1;
}

void cursorCallback(GLFWwindow* window, double xPos, double yPos)
{	
	Vector2 mousePos((float) tCord(xPos, WIDTH), - (float) tCord(yPos, HEIGHT));
	circle->SetPosition(mousePos);
	delete(line1);
	line1 = new Line(mousePos, Vector2(-1.0f, -1.0f));
	if(timer.IsPaused())
		return;
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
	if(action == GLFW_PRESS){
		if(timer.IsPaused())
			timer.Resume();
		else
			timer.Pause();
	}
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}