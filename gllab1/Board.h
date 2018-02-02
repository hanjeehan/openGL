//
// Created by yaozun on 2/2/18.
//

#ifndef OPENGL_BOARD_H
#define OPENGL_BOARD_H

#include <glm/detail/type_mat4x4.hpp>
#include "Loader.h"

class Board {
public:
    Board(int size, int nsquare);

    void draw(glm::mat4 model, glm::mat4 view, glm::mat4 proj);

private:
    ShaderProgram * shaderProgram;
    //need to create so called VAO vertex array object
    GLuint VAO;
    int size;
    int nsquare;
};
#endif //OPENGL_BOARD_H
