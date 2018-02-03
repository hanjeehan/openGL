
#include "MyGlWindow.h"
#include "ColorCube.h"
#include <glm/gtc/type_ptr.hpp>

static float DEFAULT_VIEW_POINT[3] = { 5, 5, 5 };
static float DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
static float DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };

MyGlWindow::MyGlWindow(int w, int h)

//==========================================================================
{
	m_width = w;
	m_height = h;

    //m_cube = new ColorCube();
    m_sphere = new Sphere(2.0, 50, 50);
    glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    m_pot = new VBOTeapot(64, m);
    m_board = new Board(50, 16);

    glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
    glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
    glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);

    float aspect = (w / (float) h);
    m_viewer = new Viewer(viewPoint, viewCenter, upVector, 45.0f, aspect);
}


void MyGlWindow::setSize(int w, int h)
{
	m_width = w;
	m_height = h;

}

void MyGlWindow::setAspect(float f){
    m_aspect = f;
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
    //m_model.glTranslate(1 * step, 1 * step, 1 * step);
    //m_model.glRotate(45.0, 0.1, 0.1, 0.1);

    glm::vec3 eye = m_viewer->getViewPoint();
    glm::vec3 look = m_viewer->getViewCenter();
    glm::vec3 up = m_viewer->getUpVector();

    glm::mat4 model = m_model.getMatrix();
    auto baseModel = model;

    glm::mat4 view = lookAt(eye, look, up);

    glm::mat4 proj = glm::perspective(
            45.0f, //field of view
            static_cast<float>(m_width) / static_cast<float>(m_height), //width / height ratio
            0.1f, // near
            300.0f // far
    );


    //if (m_cube)
    //    m_cube->draw(model, view, proj);
    if (m_board)
        m_board->draw(model, view, proj);
    m_model.glPushMatrix();
    m_model.glTranslate(0.0, 15.0, 0.0);
    model = baseModel * m_model.getMatrix();
    if (m_sphere)
        m_sphere->draw(model, view, proj);
    m_model.glPopMatrix();
    m_model.glPushMatrix();
    m_model.glTranslate(0.0, 5.0, 0.0);
    m_model.glRotate(90.0, 1.0, 0.0, 0.0);
    m_model.glRotate(180.0, 0.0, 1.0, 0.0);
    m_model.glScale(3.0, 3.0, 3.0);
    model = baseModel * m_model.getMatrix();
    if (m_pot)
        m_pot->draw(model, view, proj);
    m_model.glPopMatrix();
    m_model.glPopMatrix();
}
