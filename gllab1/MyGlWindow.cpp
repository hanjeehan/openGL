
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

    float step = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / 1000) - 500.0f;
    step /= 1000;
    m_model.glPushMatrix();
    //m_model.glTranslate(1 * step, 1 * step, 0);
    //m_model.glRotate(45.0, 0.1, 0.1, 0.1);

    glm::vec3 eye(5, 5, 5), center(0, 0, 0), up(0, 1, 0);
    glm::mat4 view = glm::lookAt(eye, center, up);

    glm::mat4 proj = glm::perspective(
            45.0f,
            static_cast<float>(m_width) / static_cast<float>(m_height),
            0.1f,
            300.0f
    );

    if (m_cube)
        m_cube->draw(m_model.getMatrix(), view, proj);
}
