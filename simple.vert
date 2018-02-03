#version 420 //opengl version 4.0.0

in vec3 coord3d;
in vec3 v_color;

//uniform mat4 translate;
//uniform mat4 rotate;

//uniform mat4 model, view, proj; //local->global->camera->clipped

uniform mat4 mvp;

out vec3 color; //all out become in of frag

void main()
{
    //gl_Position in built variable that must be set
    //gl_Position = translate * rotate * coord3d;
    //gl_Position = model * coord3d;
    //gl_Position = proj * view * model * vec4(coord3d, 1.0);
    gl_Position = mvp * vec4(coord3d, 1.0);
    color = v_color;
}