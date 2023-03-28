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
uniform vec3 cameraPosition;
uniform mat4 model;
uniform mat4 view;
uniform mat3 normalMatrix;

void main() {
	vec3 ambient = light.color * light.ambientStrength;

	vec3 normalInViewSpace = normalize(normalMatrix * Normal);
	vec3 fragmentPositionInViewSpace = (view * model * vec4(FragmentPosition, 1.0)).xyz;

	vec3 lightPositionView = (view * vec4(light.position, 1.0f)).xyz;
	vec3 lightDirection = normalize(lightPositionView - fragmentPositionInViewSpace);

	float diff = max(dot(normalInViewSpace, lightDirection), 0.0f);
	vec3 diffuse = diff * light.color;

	// Add specular lighting
	float specularStrength = 0.5f;
	vec3 viewPositionInViewSpace = (view * vec4(cameraPosition, 1.0)).xyz;
	vec3 viewDirection = normalize(viewPositionInViewSpace - fragmentPositionInViewSpace);
	vec3 reflectDirection = reflect(-lightDirection, normalInViewSpace);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
	vec3 specular = specularStrength * spec * light.color;

	vec4 textureColor = texture2D(texture, TextureCoord);
	vec3 result = (ambient + diffuse + specular) * vec3(textureColor.x, textureColor.y, textureColor.z);
	fColor = vec4(result, 1.0f);
}