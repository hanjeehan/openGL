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

    void draw();

private:
    ShaderProgram * shaderProgram;
    //need to create so called VAO vertex array object
    GLuint VAO;
    Model m_model;
};


#endif //OPENGL_COLORCUBE_H
