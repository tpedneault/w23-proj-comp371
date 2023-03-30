#version 410 core

layout (location = 0) out vec4 fColor;

in vec3 TextureCoord;

uniform samplerCube skybox;

void main()
{
    fColor = texture(skybox, TextureCoord);
}