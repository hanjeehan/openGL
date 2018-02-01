#include <iostream>
#include "GL/glew.h"
#include <string>
#include <stack>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtx/transform.hpp"


#include "Loader.h"

class MyGlWindow {
public:
	MyGlWindow(int w, int h);
	void draw();
	void setSize(int w, int h);
private:
	int m_width;
	int m_height;
	ShaderProgram * shaderProgram;
	void setupBuffer();
};
