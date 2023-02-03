#version 450 core

layout (location = 0) in vec4 vPosition;

void main() {
	gl_Position = vec4(vPosition.x * -1, vPosition.y * -1, vPosition.z * -1, 1.0f);
}