#version 400

in vec3 Position;
in vec3 Normal;

uniform vec4 LightPosition = vec4(10.0, 10.0, 10.0, 1.0);
uniform vec3 LightIntensity;

varying vec3 color;
//varying vec3 fNormal; // varying = out
//varying vec3 fPosition;

const vec3 Kd = vec3(0.0215,  0.1745,   0.0215); // diffuse object colors
const vec3 Ld = vec3(0.5, 0.5, 0.5); // diffuse light colors
const vec3 Ka = vec3(0.07568, 0.61424,  0.07568); // ambient object colors
const vec3 La = vec3(0.5, 0.5, 0.5); // ambient light colors
const vec3 Ks = vec3(0.633,   0.727811, 0.633); // specular object colors
const vec3 Ls = vec3(0.5, 0.5, 0.5); // specular light colors

void main() {
    FragColor = vec4(color, 1.0);
}
