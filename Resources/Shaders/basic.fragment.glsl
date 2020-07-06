#version 330 core
out vec4 FragColor;  



in vec3 FragPos;
in vec3 theNormal;  
in vec2 TexCoords;
in vec3 mViewPos;
in vec3 lightPos;

uniform sampler2D texture_diffuse1;


struct Material {

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;

};
uniform Material material;

void main()
{



	//float ambient = 0.2;
	float lightStrength =1.0;
	float specularStrength = 0.5;
	vec3 lightColor = vec3(0.5f,0.5f,1.0f);

	//ambient
	vec3 ambient = lightColor * material.ambient;

	//diffuse
	vec3 norm = normalize(theNormal);
	vec3 lightDir = normalize(lightPos - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = lightColor * (diff );

	//specular
	vec3 viewDir = normalize(mViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  
	vec4 result = vec4((ambient + diff + specular),1.0f);

	FragColor = texture(texture_diffuse1, TexCoords) * result ;


}