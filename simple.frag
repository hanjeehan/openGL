#version 420 //opengl version 4.0.0


in vec3 color;

out vec4 fragColor; //frag shader must have at least one out

void main()
{
    fragColor = vec4(color, 1.0);
}