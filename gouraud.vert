#version 420

//precision highp float;


attribute vec3 VertexPosition;
attribute vec3 VertexNormal;

uniform mat3 normalMatrix;
uniform mat4 mv;
uniform mat4 p;

varying vec3 Position;
varying vec3 Normal;

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
  vec3 specular = Ks * Ls * pow(max(dot(R, V), 0.0), 76.8);
  color = diffuse + ambient + specular;
  gl_Position = p * pos;
}
