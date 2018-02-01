
#include "MyGlWindow.h"
#include <glm/gtc/type_ptr.hpp>

MyGlWindow::MyGlWindow(int w, int h)

//==========================================================================
{
	m_width = w;
	m_height = h;

	setupBuffer();
}


void MyGlWindow::setSize(int w, int h)
{
	m_width = w;
	m_height = h;

}


void MyGlWindow::setupBuffer()
{
	//make an instance od shader object
    shaderProgram = new ShaderProgram();

    //vertex shader = simple.vert fragment shader = simple.frag
    shaderProgram->initFromFiles("simple.vert", "simple.frag");

    //three vertices
    const auto vertexPosition[] = {
            -0.2f, 0,    0, 1,
            0,     0.4f, 0, 1,
            0.2f,  0,    0, 1
    };
    const auto vertexColors[] = {
            1, 0, 0, //red
            0, 1, 0, //blue
            0, 0, 1  //green
    };

    //need to create so called VAO vertex array object

}

void MyGlWindow::draw(void)
{
	
	glClearColor(0.2f, 0.2f, .2f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glEnable(GL_DEPTH_TEST);
	
	glViewport(0, 0, m_width, m_height);	


}
