#version 110
uniform mat4 MVP;
//attribute vec3 vCol;
//attribute vec2 vPos;
varying vec3 color;

void main()
{
	gl_Position = MVP * vec4(0.0, 0.0, 0.0, 1.0);
	color = vec3(1.0, 1.0, 0.0);
}