
#include "MyGlWindow.h"
#include "ColorCube.h"
#include <glm/gtc/type_ptr.hpp>

MyGlWindow::MyGlWindow(int w, int h)

//==========================================================================
{
	m_width = w;
	m_height = h;

    m_cube = new ColorCube();
}


void MyGlWindow::setSize(int w, int h)
{
	m_width = w;
	m_height = h;

}

void MyGlWindow::draw(void)
{
    //background color
	glClearColor(0.2f, 0.2f, 0.2f, 0);
    //clear buffers (color and depth)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	//set the canvas, 0 0 bottom
	glViewport(0, 0, m_width, m_height);
    m_cube->draw();
}
