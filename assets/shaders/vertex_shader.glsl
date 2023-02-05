#version 450 core

layout (location = 0) in vec4 vPosition;

out vec4 fragColor;

uniform mat4 mvp;
uniform vec3 color = vec3(25.0f, 25.0f, 25.0f);

void main() {
	gl_Position = mvp * vec4(vPosition.x * -1, vPosition.y * -1, vPosition.z * -1, 1.0f);
	fragColor = vec4(color.x, color.y, color.z, 1.0f);
}