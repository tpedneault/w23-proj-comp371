#version 410 core
layout (location = 0) in vec4 vPosition;

out vec2 TextureCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main() {
    TextureCoord = vPosition.xy;
    gl_Position = projection * view * model * vec4(vPosition.xyz, 1.0f);
}