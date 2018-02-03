#version 420

//precision highp float;


attribute vec3 VertexPosition;
attribute vec3 VertexNormal;

uniform mat3 normalMatrix;
uniform mat4 mv;
uniform mat4 p;

varying vec3 color;
//varying vec3 fNormal; // varying = out
//varying vec3 fPosition;

const vec3 lightPos = vec3(10.0, 10.0, 10.0);
const vec3 Kd = vec3(0.135,     0.2225,   0.1575); // diffuse object colors
const vec3 Ld = vec3(0.5, 0.5, 0.5); // diffuse light colors
const vec3 Ka = vec3(0.54,      0.89,     0.63); // ambient object colors
const vec3 La = vec3(0.2, 0.2, 0.2); // ambient light colors
const vec3 Ks = vec3(0.316228,  0.316228, 0.316228); // specular object colors
const vec3 Ls = vec3(0.5, 0.5, 0.5); // specular light colors

void main()
{
  vec4 pos = mv * vec4(VertexPosition, 1.0); // camera coord system
  vec3 N = normalize(normalMatrix * VertexNormal);
  vec3 L = normalize(lightPos - pos.xyz);
  vec3 V = normalize(-pos.xyz);
  vec3 R = normalize(reflect(-L, N));
  float dotLN = dot(L, N);
  vec3 diffuse = Kd * Ld * max(dotLN, 0.0);
  vec3 ambient = Ka * La;
  vec3 specular = Ks * Ls * pow(max(dot(R, V), 0.0), 12.8);
  color = diffuse + ambient + specular;
  gl_Position = p * pos;
}
