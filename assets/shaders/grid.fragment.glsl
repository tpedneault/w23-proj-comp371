#version 410 core

layout (location = 0) out vec4 fColor;

in vec2 vTextureCoords;

uniform float gridSize = 10.0;
uniform float lineWidth = 0.02;
uniform vec3 lineColor = vec3(0.3, 0.3, 0.3);

void main() {
    vec2 coord = fract(vTextureCoords * gridSize);
    float lineX = abs(coord.x - 0.5) < lineWidth / 2.0 ? 1.0 : 0.0;
    float lineZ = abs(coord.y - 0.5) < lineWidth / 2.0 ? 1.0 : 0.0;

    if (lineX > 0.0 || lineZ > 0.0) {
        fColor = vec4(lineColor, 1.0);
    } else {
        discard;
    }
}