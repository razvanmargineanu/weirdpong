#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;


out vec2 TexCoords;
out vec3 theNormal;
out vec3 FragPos;  
out vec3 mViewPos;
out vec3 lightPos;

uniform vec3 viewPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 alightPos;

void main()
{

    gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoords = vec2(aTexCoords.x, aTexCoords.y);

	FragPos = vec3(model * vec4(aPos, 1.0));
	theNormal = mat3(transpose(inverse(model))) * aNormal;  
	mViewPos = viewPos;
	lightPos = alightPos;
}       





