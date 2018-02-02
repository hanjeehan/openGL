
#include "MyGlWindow.h"
#include <glm/gtc/type_ptr.hpp>

//need to create so called VAO vertex array object
GLuint VAO;

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
    const float vertexPosition[] = {
            -0.2f, 0,    0, 1,
            0,     0.4f, 0, 1,
            0.2f,  0,    0, 1
    };
    const float vertexColors[] = {
            1, 0, 0, //red
            0, 1, 0, //blue
            0, 0, 1  //green
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    shaderProgram->addAttribute("coord3d");
    shaderProgram->addAttribute("v_color");

    //shaderProgram->addUniform("translate");
    //shaderProgram->addUniform("rotate");

    shaderProgram->addUniform("model");

    //vbo
    GLuint vbo_vertices, vbo_color;

    // create vbo
    glGenBuffers(1, &vbo_vertices);
    //bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    //allocate mem
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 3, &vertexPosition, GL_STATIC_DRAW);
    //tell gpu how to interpretate the data
    glVertexAttribPointer(
            shaderProgram->attribute("coord3d"), //location of a specific attribute
            4, // how many data for each vertex
            GL_FLOAT, // type
            GL_FALSE,
            0,
            0
    );
    glEnableVertexAttribArray(shaderProgram->attribute("coord3d"));

    // create vbo
    glGenBuffers(1, &vbo_color);
    //bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
    //allocate mem
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, &vertexColors, GL_STATIC_DRAW);
    //tell gpu how to interpretate the data
    glVertexAttribPointer(
            shaderProgram->attribute("v_color"), //location of a specific attribute
            3, // how many data for each vertex
            GL_FLOAT, // type
            GL_FALSE,
            0,
            0
    );
    glEnableVertexAttribArray(shaderProgram->attribute("v_color"));

    //close vao
    glBindVertexArray(0);
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
    //use this shader
    shaderProgram->use();
    glBindVertexArray(VAO);

    //glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0));
    //glm::mat4 rotate = glm::rotate(45.0f, glm::vec3(0.3f, 0.3f, 0));
    //glUniformMatrix4fv(shaderProgram->uniform("translate"), 1, GL_FALSE, glm::value_ptr(translate));
    //glUniformMatrix4fv(shaderProgram->uniform("rotate"), 1, GL_FALSE, glm::value_ptr(rotate));

    float step = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / 1000) - 500.0f;
    step /= 10000;
    m_model.glPushMatrix();
    m_model.glTranslate(1 * step, 1 * step, 0);
    m_model.glRotate(45.0, 0.1, 0.1, 0.1);
    glUniformMatrix4fv(shaderProgram->uniform("model"), 1, GL_FALSE, glm::value_ptr(m_model.getMatrix()));
    //what to draw
    glDrawArrays(GL_TRIANGLES, 0, 3);
    shaderProgram->disable();
}
