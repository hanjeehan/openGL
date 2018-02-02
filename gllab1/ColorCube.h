//
// Created by yaozun on 2/2/18.
//

#ifndef OPENGL_COLORCUBE_H
#define OPENGL_COLORCUBE_H


#include "Loader.h"
#include "ModelView.h"

class ColorCube {
public:
    ColorCube();

    void draw(glm::mat4 model, glm::mat4 view, glm::mat4 proj);

private:
    ShaderProgram * shaderProgram;
    //need to create so called VAO vertex array object
    GLuint VAO;
};


#endif //OPENGL_COLORCUBE_H
