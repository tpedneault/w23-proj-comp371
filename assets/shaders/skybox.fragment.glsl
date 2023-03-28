#version 410 core

out vec4 FragColor;
in vec2 TextureCoord;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, vec3(TextureCoord.xy, 1.0f));
}