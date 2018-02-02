
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
    /*const float vertexPosition[] = {
            0.0f,  0,    0, 1,
            0,     0.5f, 0, 1,
            0.5f,  0,    0, 1,
            0.5f,  0,    0, 1,
            0,     0.5f, 0, 1,
            0.5f,  0.5f, 0, 1
    };
    const float vertexColors[] = {
            1, 0, 0, //red
            0, 1, 0, //blue
            0, 0, 1,  //green
            0, 0, 1, //green
            0, 1, 0, //blue
            1, 0, 0  //red
    };*/
    GLfloat cube_vertices[] = {
    // front
            -1.0, -1.0, 1.0,
            1.0, -1.0, 1.0,
            1.0, 1.0, 1.0,
            -1.0, 1.0, 1.0,
    // back
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0, 1.0, -1.0,
            -1.0, 1.0, -1.0,
    };

    GLfloat cube_colors[] = {
    // front colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
    // back colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    shaderProgram->addAttribute("coord3d");
    shaderProgram->addAttribute("v_color");

    //shaderProgram->addUniform("translate");
    //shaderProgram->addUniform("rotate");

    //shaderProgram->addUniform("model");

    //vbo
    GLuint vbo_vertices, vbo_color;

    // create vbo
    glGenBuffers(1, &vbo_vertices);
    //bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    //allocate mem
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 8, &cube_vertices, GL_STATIC_DRAW);
    //tell gpu how to interpretate the data
    glVertexAttribPointer(
            shaderProgram->attribute("coord3d"), //location of a specific attribute
            3, // how many data for each vertex
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 8, &cube_colors, GL_STATIC_DRAW);
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

    GLuint ibo_cube_elements;
    GLushort cube_elements[] = {
            0, 1, 2,		2, 3, 0,		1, 5, 6,
            6, 2, 1,		7, 6, 5,		5, 4, 7,
            4, 0, 3,		3, 7, 4,		4, 5, 1,
            1, 0, 4,		3, 2, 6,		6, 7, 3,
    };
    glGenBuffers(1, &ibo_cube_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

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

    /*float step = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / 1000) - 500.0f;
    step /= 10000;
    m_model.glPushMatrix();
    m_model.glTranslate(1 * step, 1 * step, 0);
    m_model.glRotate(45.0, 0.1, 0.1, 0.1);
    glUniformMatrix4fv(shaderProgram->uniform("model"), 1, GL_FALSE, glm::value_ptr(m_model.getMatrix()));*/
    //what to draw
    //VAO
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //with IBO
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE,&size);
    glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    shaderProgram->disable();
}
