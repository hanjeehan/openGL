#include <iostream>
#include "GL/glew.h"
#include <string>
#include <stack>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtx/transform.hpp"

#include "Loader.h"
#include "ModelView.h"
#include "ColorCube.h"
#include "Viewer.h"
#include "Board.h"

class MyGlWindow {
public:
	MyGlWindow(int w, int h);
	void draw();
	void setSize(int w, int h);
    void setAspect(float f);
    Viewer *m_viewer;
private:
	int m_width;
	int m_height;
    float m_aspect;
    Model m_model;
    ColorCube *m_cube;
    Board * m_board;
};
