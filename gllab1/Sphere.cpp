#include "Sphere.h"

#include <glm//gtc/constants.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>


Sphere::Sphere()
{

}


Sphere::~Sphere()
{
}



Sphere::Sphere(float rad, GLuint sl, GLuint st) :
radius(rad), slices(sl), stacks(st)
{
	
	nVerts = (slices + 1) * (stacks + 1);
	elements = (slices * 2 * (stacks - 1)) * 3;

	// Verts
	float * v = new float[3 * nVerts];
	// Normals
	float * n = new float[3 * nVerts];
	// Tex coords
	float * tex = new float[2 * nVerts];
	// Elements
	unsigned int * el = new unsigned int[elements];

	// Generate the vertex data
	generateVerts(v, n, tex, el);




	shaderProgram = new ShaderProgram();
	shaderProgram->initFromFiles("gouraud.vert", "gouraud.frag");

	//add attributes and uniform vars
	shaderProgram->addAttribute("VertexPosition");
	shaderProgram->addAttribute("VertexNormal");

    shaderProgram->addUniform("normalMatrix");
    shaderProgram->addUniform("mv");
    shaderProgram->addUniform("p");

	// Create the VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);



	// Create and populate the buffer objects
	unsigned int handle[3];
	glGenBuffers(3, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), v, GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("VertexPosition"), // attribute
		3,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
	glEnableVertexAttribArray(shaderProgram->attribute("VertexPosition"));

	

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), n, GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("VertexNormal"), // attribute
		3,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
	glEnableVertexAttribArray(shaderProgram->attribute("VertexNormal"));

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(unsigned int), el, GL_STATIC_DRAW);

	delete[] v;
	delete[] n;
	delete[] el;
	delete[] tex;

	
	glBindVertexArray(0);
}

void Sphere::draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection) 
{

	shaderProgram->use();

	glBindVertexArray(VAO);
	glm::tmat4x4 mv = view * model;
    glm::mat4 inv = glm::inverseTranspose(mv);
    glm::mat3 normalMatrix = glm::mat3(inv);
    glUniformMatrix3fv(shaderProgram->uniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glUniformMatrix4fv(shaderProgram->uniform("mv"), 1, GL_FALSE, glm::value_ptr(mv));
    glUniformMatrix4fv(shaderProgram->uniform("p"), 1, GL_FALSE, glm::value_ptr(projection));
	glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
	glBindVertexArray(0);

	shaderProgram->disable();

}

void Sphere::generateVerts(float * verts, float * norms, float * tex,
	unsigned int * el)
{
	// Generate positions and normals
	GLfloat theta, phi;
	GLfloat thetaFac = glm::two_pi<float>() / slices;
	GLfloat phiFac = glm::pi<float>() / stacks;
	GLfloat nx, ny, nz, s, t;
	GLuint idx = 0, tIdx = 0;
	for (GLuint i = 0; i <= slices; i++) {
		theta = i * thetaFac;
		s = (GLfloat)i / slices;
		for (GLuint j = 0; j <= stacks; j++) {
			phi = j * phiFac;
			t = (GLfloat)j / stacks;
			nx = sinf(phi) * cosf(theta);
			ny = sinf(phi) * sinf(theta);
			nz = cosf(phi);
			verts[idx] = radius * nx; verts[idx + 1] = radius * ny; verts[idx + 2] = radius * nz;
			norms[idx] = nx; norms[idx + 1] = ny; norms[idx + 2] = nz;
			idx += 3;

			tex[tIdx] = s;
			tex[tIdx + 1] = t;
			tIdx += 2;
		}
	}

	// Generate the element list
	idx = 0;
	for (GLuint i = 0; i < slices; i++) {
		GLuint stackStart = i * (stacks + 1);
		GLuint nextStackStart = (i + 1) * (stacks + 1);
		for (GLuint j = 0; j < stacks; j++) {
			if (j == 0) {
				el[idx] = stackStart;
				el[idx + 1] = stackStart + 1;
				el[idx + 2] = nextStackStart + 1;
				idx += 3;
			}
			else if (j == stacks - 1) {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j;
				idx += 3;
			}
			else {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j + 1;
				el[idx + 3] = nextStackStart + j;
				el[idx + 4] = stackStart + j;
				el[idx + 5] = nextStackStart + j + 1;
				idx += 6;
			}
		}
	}
}

int Sphere::getVertexArrayHandle() 
{
	return this->VAO;
}

