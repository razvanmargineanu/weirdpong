#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aVertexColor;

out vec2 TexCoords;
out vec3 theNormal;
out vec3 FragPos;  
out vec3 mViewPos;
out vec3 lightPos;
out vec3 vertexColor;

uniform vec3 viewPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 alightPos;

void main()
{
	vec4 Tcoord;
    gl_Position = projection * view * model * vec4(aPos, 1.0);

	Tcoord = vec4(aTexCoords.y, 1.0f, aTexCoords.x,0.0f);
	//Tcoord =  projection * view * vec4(aTexCoords.y, 1.0f, aTexCoords.x,0.0f);
	TexCoords = vec2(Tcoord.x, Tcoord.z);
	FragPos = vec3(model * vec4(aPos, 1.0));
	theNormal = mat3(transpose(inverse(model))) * aNormal;  
	mViewPos = viewPos;
	lightPos = alightPos;
	vertexColor = aVertexColor;
}       





