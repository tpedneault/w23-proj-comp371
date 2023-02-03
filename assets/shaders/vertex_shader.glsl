#version 450 core

layout (location = 0) in vec4 vPosition;

uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(vPosition.x * -1, vPosition.y * -1, vPosition.z * -1, 1.0f);
}