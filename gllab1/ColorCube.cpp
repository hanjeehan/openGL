//
// Created by yaozun on 2/2/18.
//

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "ColorCube.h"

ColorCube::ColorCube(){
    std::vector<glm::vec3> cube_vertices;
    //front
    cube_vertices.push_back(glm::vec3(0, 0, 2.0));
    cube_vertices.push_back(glm::vec3(2.0, 0, 2.0));
    cube_vertices.push_back(glm::vec3(2, 2, 2));
    cube_vertices.push_back(glm::vec3(0, 2, 2));
    // back
    cube_vertices.push_back(glm::vec3(0, 0, 0));
    cube_vertices.push_back(glm::vec3(2, 0, 0));
    cube_vertices.push_back(glm::vec3(2, 2, 0));
    cube_vertices.push_back(glm::vec3(0, 2, 0));

    std::vector<glm::vec3> cube_colors;
    // front colors
    cube_colors.push_back(glm::vec3(1.0, 0.0, 0.0));
    cube_colors.push_back(glm::vec3(0.0, 1.0, 0.0));
    cube_colors.push_back(glm::vec3(0.0, 0.0, 1.0));
    cube_colors.push_back(glm::vec3(1.0, 1.0, 1.0));
    // back colors
    cube_colors.push_back(glm::vec3(1.0, 0.0, 0.0));
    cube_colors.push_back(glm::vec3(0.0, 1.0, 0.0));
    cube_colors.push_back(glm::vec3(0.0, 0.0, 1.0));
    cube_colors.push_back(glm::vec3(1.0, 1.0, 1.0));

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

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    shaderProgram->addAttribute("coord3d");
    shaderProgram->addAttribute("v_color");

    //shaderProgram->addUniform("translate");
    //shaderProgram->addUniform("rotate");

    shaderProgram->addUniform("mvp");

    //vbo
    GLuint vbo_vertices, vbo_color;

    // create vbo
    glGenBuffers(1, &vbo_vertices);
    //bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    //allocate mem
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * cube_vertices.size(), cube_vertices.data(), GL_STATIC_DRAW);
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * cube_colors.size(), cube_colors.data(), GL_STATIC_DRAW);
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

void ColorCube::draw(glm::mat4 model, glm::mat4 view, glm::mat4 proj){
    //use this shader
    shaderProgram->use();
    glBindVertexArray(VAO);

    //glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0));
    //glm::mat4 rotate = glm::rotate(45.0f, glm::vec3(0.3f, 0.3f, 0));
    //glUniformMatrix4fv(shaderProgram->uniform("translate"), 1, GL_FALSE, glm::value_ptr(translate));
    //glUniformMatrix4fv(shaderProgram->uniform("rotate"), 1, GL_FALSE, glm::value_ptr(rotate));

    glm::mat4 mvp = proj * view * model;
    glUniformMatrix4fv(shaderProgram->uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
    //glUniformMatrix4fv(shaderProgram->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    //glUniformMatrix4fv(shaderProgram->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    //what to draw
    //VAO
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //with IBO
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE,&size);
    glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    shaderProgram->disable();

}