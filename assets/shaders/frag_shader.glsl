#version 410 core

struct Light {
	vec3 position;
	vec3 color;
	float ambientStrength;
};

uniform Light light;

layout (location = 0) out vec4 fColor;

in vec3 FragmentPosition;
in vec3 Normal;

void main() {
	vec3 ambient = light.color * light.ambientStrength;
	vec3 modelColor = vec3(1.0f, 0.1f, 0.1f);

	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(light.position - FragmentPosition);

	float diff = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = diff * light.color;

	vec3 result = (ambient + diffuse) * modelColor;
	fColor = vec4(result, 1.0f);
}