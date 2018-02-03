#version 420 //opengl version 4.0.0

in vec3 color;

out vec4 fragColor; //frag shader must have at least one out

void main()
{
    fragColor = vec4(color, 1.0);
}

/*

precision highp float;
uniform float time;
uniform vec2 resolution;
varying vec3 fPosition;
varying vec3 color;

void main()
{
  gl_FragColor = vec4(color, 1.0);
}

*/