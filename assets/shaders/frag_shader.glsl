#version 410 core

struct Light {
	vec3 position;
	vec3 color;
	float ambientStrength;
};

uniform Light light;

layout (location = 0) out vec4 fColor;

in vec3 FragmentPosition;
in vec2 TextureCoord;
in vec3 Normal;

uniform sampler2D texture;

void main() {
	vec3 ambient = light.color * light.ambientStrength;

	vec3 norm = abs(normalize(Normal));
	vec3 lightDirection = normalize(light.position - FragmentPosition);

	float diff = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = diff * light.color;

	vec4 textureColor = texture2D(texture, TextureCoord);
	vec3 result = (ambient + diffuse) * vec3(0.7f, 0.6f, 0.5f);
	fColor = vec4(result, 1.0f);
}