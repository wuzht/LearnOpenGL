#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform int flag = 0;

void main()
{
	if (flag == 0 || flag == 2) {
		FragColor = vec4(ourColor, 1.0f);
	}
	else if (flag == 1) {
		// linearly interpolate between both textures (80% container, 20% awesomeface)
		FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	}
}