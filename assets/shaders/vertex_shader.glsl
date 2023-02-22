#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vTextureCoords;
layout (location = 2) in vec3 vNormals;

uniform mat4 mvp;

void main() {
	gl_Position = mvp * vec4(vPosition.x, vPosition.y, vPosition.z, 1.0f);
}