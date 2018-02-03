#ifndef ___SPHERE_H
#define ___SPHERE_H

#include "GL/glew.h"
#include <GL/gl.h>
#include <glm/mat4x4.hpp>

#include <vector>

#include "Loader.h"


class Sphere
{
public:
	Sphere();
	Sphere(float rad, GLuint sl, GLuint st);
	~Sphere();

	void draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection);
	int getVertexArrayHandle();

	GLuint VAO, VBO_position, VBO_normal, IBO;

	ShaderProgram *shaderProgram;

private:
	GLuint nVerts, elements;
	float radius;
	GLuint slices, stacks;

	void generateVerts(float *, float *, float *, GLuint *);


};


#endif
