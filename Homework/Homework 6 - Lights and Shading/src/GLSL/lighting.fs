#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightingColor;

uniform int isPhong;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform int shininess;

void main() {
	if (isPhong == 1) {	// Phong shading
		// ambiant
		vec3 ambient = ambientStrength * lightColor;

		// diffuse
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diffuseStrength * diff * lightColor;

		// specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
		vec3 specular = specularStrength * spec * lightColor; 

		vec3 result = (ambient + diffuse + specular) * objectColor;
		FragColor = vec4(result, 1.0f);
	}
	else { // Gouraud shading
		FragColor = vec4(LightingColor * objectColor, 1.0);
	}
}