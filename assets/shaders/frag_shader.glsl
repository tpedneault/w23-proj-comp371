#version 410 core

struct Light {
	vec3 position;
	vec3 color;
	float ambientStrength;
};

uniform Light light;

layout (location = 0) out vec4 fColor;

void main() {
	vec3 ambient = light.color * light.ambientStrength;
	vec3 modelColor = vec3(1.0f, 0.1f, 0.1f);

	vec3 result = modelColor * ambient;
	fColor = vec4(result, 1.0f);
}