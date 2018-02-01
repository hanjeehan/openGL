#version 420 //opengl version 4.0.0

in vec4 coord3d;
in vec3 v_color;

uniform mat4 translate;
uniform mat4 rotate;

//uniform mat4 model;

out vec3 color; //all out become in of frag

void main()
{
    //gl_Position in built variable that must be set
    gl_Position = translate * rotate * coord3d;
    //gl_Position = model * coord3d;
    color = v_color;
}