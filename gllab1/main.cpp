
//#define GLFW_INCLUDE_GLU

#include <iostream>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/gtx/string_cast.hpp>
#include <thread>


#include "MyGlWindow.h"

MyGlWindow * win;

bool lbutton_down;
bool rbutton_down;
bool mbutton_down;
double m_lastMouseX;
double m_lastMouseY;
double cx, cy;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	win->setSize(width, height);
}

void exercice1(){
    // Move point p(1, 4, -5) to vector v(5, 1, 4)
    glm::vec3 p(1, 4, -5);
    glm::vec3 v(5, 1, 4);

    p += v;
    std::cout << glm::to_string(p) << std::endl;

    //Add vector v1(1,0,0) and vector v2(0,1,0)
    glm::vec3 v1(1, 0, 0);
    glm::vec3 v2(0, 1, 0);

    auto v3 = v1 + v2;
    std::cout << glm::to_string(v3) << std::endl;

    //Multiply v1(0,1,0) with  scalar 5.
    glm::vec3 v11(0, 1, 0);

    v11 *= 5;
    std::cout << glm::to_string(v11) << std::endl;

    //Get a vector v starting at (8,2,5) and ending at (1,-1,4)

    //Normalize vector v(1,3,4).
}

int main(void)
{
//    glm::vec3 a(1, 2, 3);
//    glm::vec3 b(-1, 0, -2);
//
//    //add
//    auto c = a + b;
//    auto len = glm::length(c);
//    //normalized
//    c = glm::normalize(c);
//    //cant do c.normalize(); nor c.length();
//    c *= 3;
//    c = c * 3.0f; // can't c * 3;
//
//    std::cout << glm::to_string(c) << std::endl;

//    exercice1();

    std::srand(static_cast<unsigned>(std::time(nullptr)));
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 800;
	int height = 800;


	window = glfwCreateWindow(width, height, "Chinese food is good", NULL, NULL);


	if (!window)
	{
	glfwTerminate();
	return -1;
	}



	glfwMakeContextCurrent(window);
	
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
	//Problem: glewInit failed, something is seriously wrong.
	fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	return 0;
	}

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
	glGetString(GL_SHADING_LANGUAGE_VERSION));


	glfwSwapInterval(1);  //enable vsync

	
	win = new MyGlWindow(width, height);

	
	double previousTime = glfwGetTime();
	int frameCount = 0;
	double lastTime;

	
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	glfwSetWindowTitle(window, "Chinese food is good");

    glm::vec3 eye(0, -10, 2), center(0, 0, 0), up(0, 0, 1);
    glm::lookAt(eye, center, up);

	while (!glfwWindowShouldClose(window))
	{



	// Rendering
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);

	win->draw();

	
	glfwSwapBuffers(window);


	glfwPollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}


