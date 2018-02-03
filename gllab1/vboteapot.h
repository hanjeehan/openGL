#ifndef VBOTEAPOT_H
#define VBOTEAPOT_H




#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "Loader.h"

using glm::vec4;
using glm::vec3;
using glm::mat3;
using glm::mat4;

class VBOTeapot
{
private:
    unsigned int vaoHandle;
    unsigned int faces, vbo_vertices, vbo_normals, ibo_elements;
	ShaderProgram *shaderProgram;
    void generatePatches(float * v, float * n, float *tc, unsigned int* el, int grid);
    void buildPatchReflect(int patchNum,
                           float *B, float *dB,
                           float *v, float *n, float *, unsigned int *el,
                           int &index, int &elIndex, int &, int grid,
                           bool reflectX, bool reflectY);
    void buildPatch(vec3 patch[][4],
                    float *B, float *dB,
                    float *v, float *n,float *, unsigned int *el,
                    int &index, int &elIndex, int &, int grid, mat3 reflect, bool invertNormal);
    void getPatch( int patchNum, vec3 patch[][4], bool reverseV );

    void computeBasisFunctions( float * B, float * dB, int grid );
    vec3 evaluate( int gridU, int gridV, float *B, vec3 patch[][4] );
    vec3 evaluateNormal( int gridU, int gridV, float *B, float *dB, vec3 patch[][4] );
    void moveLid(int,float *,mat4);

public:
    VBOTeapot(int grid, mat4 lidTransform);
	void draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection) const;
};

#endif // VBOTEAPOT_H
