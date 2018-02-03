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

/*
#ifdef VS

// All light calc must be done in camera coordinates system

precision highp float;

attribute vec3 position; // attribute = in, local coordinate
attribute vec3 normal;

uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

varying vec3 color;
//varying vec3 fNormal; // varying = out
//varying vec3 fPosition;

const vec3 lightPos = vec3(0.0, 5.0, 0.0);
const vec3 Kd = vec3(1.0, 0.0, 0.0); // diffuse object colors
const vec3 Ld = vec3(1.0, 1.0, 1.0); // diffuse light colors
const vec3 Ka = vec3(0.3, 0.3, 0.0); // ambient object colors
const vec3 La = vec3(0.3, 0.3, 0.3); // ambient light colors
const vec3 Ka = vec3(1.0, 1.0, 0.0); // ambient object colors
const vec3 La = vec3(1.0, 1.0, 1.0); // ambient light colors
void main()
{
  vec4 pos = modelViewMatrix * vec4(position, 1.0); // camera coord system

  vec3 N = normalize(normalMatrix * normal);
  vec3 L = normalize(lightPos - pos.xyz);
  vec3 V = normalize(-pos.xyz);
  vec3 R = normalize(reflect(-L, N));
  float dotLN = dot(L, N);
  vec3 diffuse = Kd * Ld * max(dotLN, 0.0);
  vec3 ambient = Ka * La;
  vec3 specular = Ks * Ls * pow(max(dot(R, V), 0.0), 30.0);
  color = diffuse + ambient + specular;
  gl_Position = projectionMatrix * pos;
}

#else

precision highp float;
uniform float time;
uniform vec2 resolution;
varying vec3 fPosition;
varying vec3 color;

void main()
{
  gl_FragColor = vec4(color, 1.0);
}

#endif
*/