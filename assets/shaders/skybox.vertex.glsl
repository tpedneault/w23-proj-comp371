#version 410 core
layout (location = 0) in vec4 vPosition;

out vec3 TextureCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main() {
    vec4 pos = projection * view * vec4(vPosition.xyz, 1.0f);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    TextureCoord = vec3(vPosition.x, vPosition.y, -vPosition.z);
}