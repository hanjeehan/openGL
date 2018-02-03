//
// Created by yaozun on 2/2/18.
//

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Board.h"

Board::Board(int size, int nsquare) : size(size), nsquare(nsquare)
{

    float dark[3] = { 0, 0, 0};
    float light[3] = { 1, 0, 0};
    std::vector<glm::vec3> vlist;
    std::vector<glm::vec3> clist;
    float min = -size / 2, max = size / 2;
    int x, y, i;
    bool color = true;
    float xp, yp, d = (max - min) / static_cast<float>(nsquare);

    for(x = 0, xp = min; x < nsquare; ++x, xp += d){
        for (y = 0, yp = min, i = x; y < nsquare; y++, i++, yp += d) {
            vlist.emplace_back(xp, 0, yp);
            vlist.emplace_back(xp + d, 0, yp);
            vlist.emplace_back(xp, 0, yp + d);
            vlist.emplace_back(xp + d, 0, yp + d);
            vlist.emplace_back(xp, 0, yp + d);
            vlist.emplace_back(xp + d, 0, yp);
            for(int k = 0; k < 6; ++k) {
                if (color)
                    clist.emplace_back(dark[0], dark[1], dark[2]);
                else
                    clist.emplace_back(light[0], light[1], light[2]);
            }
            color = !color;
        }
        color = !color;
    }

    shaderProgram = new ShaderProgram();
    shaderProgram->initFromFiles("simple.vert", "simple.frag");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    shaderProgram->addAttribute("coord3d");
    shaderProgram->addAttribute("v_color");

    shaderProgram->addUniform("mvp");

    GLuint vbo_vertices, vbo_color;

    // create vbo
    glGenBuffers(1, &vbo_vertices);
    //bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    //allocate mem
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * vlist.size(), vlist.data(), GL_STATIC_DRAW);
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * clist.size(), clist.data(), GL_STATIC_DRAW);
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

void Board::draw(glm::mat4 model, glm::mat4 view, glm::mat4 proj){
    shaderProgram->use();

    glBindVertexArray(VAO);
    glm::mat4 mvp = proj * view * model;
    glUniformMatrix4fv(shaderProgram->uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawArrays(GL_TRIANGLES, 0, nsquare * nsquare * 6);
    shaderProgram->disable();
}