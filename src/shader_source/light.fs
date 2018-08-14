#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material material;

in vec2 TexCoords;

struct Spotlight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

uniform Spotlight spotlight;

struct DirLight {
	vec3 direction;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 viewPos;

in vec3 outNormal;
in vec3 FragPos;

vec3 computeDirectional(DirLight light, vec3 normal, vec3 viewDir);
vec3 computePoint(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 computeSpotlight(Spotlight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
	vec3 norm = normalize(outNormal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    vec3 result = computeDirectional(dirLight, norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += computePoint(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: Spot light
    result += computeSpotlight(spotlight, norm, FragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}

vec3 computeDirectional(DirLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);
    
    float diff = max(dot(normal, lightDir), 0.0);
    
	vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
	vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

vec3 computePoint(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);
    
    float diff = max(dot(normal, lightDir), 0.0);
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 computeSpotlight(Spotlight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));
	
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);	
	
	ambient *= attenuation;
	diffuse *= intensity;
	specular *= intensity;
	
    return (ambient + diffuse + specular);
}














