// FLAT COLOR WITH LIGHTING

#type vertex
#version 330 core

layout(location = 0) in vec3 ATTR_POS;
layout(location = 1) in vec3 ATTR_NORMAL;

uniform mat4 UNI_VPM;
uniform mat4 UNI_MODELMAT;
uniform vec3 UNI_LIGHT_POSITION;

out vec3 VAR_POS;
out vec3 VAR_NORMAL;
out vec3 VAR_FRAG_POS;
out vec3 VAR_LIGHT_POSITION;

void main()
{
	VAR_POS = ATTR_POS;
	gl_Position = UNI_VPM * UNI_MODELMAT * vec4(ATTR_POS, 1.0);
	VAR_FRAG_POS = vec3(UNI_VPM * UNI_MODELMAT * vec4(ATTR_POS, 1.0));
	VAR_NORMAL = mat3(transpose(inverse(UNI_VPM * UNI_MODELMAT))) * ATTR_NORMAL;
	VAR_LIGHT_POSITION = vec3(UNI_VPM * vec4(UNI_LIGHT_POSITION, 1.0));
}

#type fragment
#version 330 core

layout(location = 0) out vec4 LOCAL_COLOR;

in vec3 VAR_POS;
in vec3 VAR_NORMAL;
in vec3 VAR_FRAG_POS;
in vec3 VAR_LIGHT_POSITION;

uniform vec4 UNI_OBJECT_COLOR;
uniform vec4 UNI_LIGHT_COLOR;

void main()
{
	// AMBIENT
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * UNI_LIGHT_COLOR.xyz;

	// DIFFUSE
	vec3 norm = normalize(VAR_NORMAL);
	vec3 lightDir = normalize(VAR_LIGHT_POSITION - VAR_FRAG_POS);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * UNI_LIGHT_COLOR.xyz;

	// SPECULAR
	float specularStrength = 0.5;
	vec3 viewDir = normalize(-VAR_FRAG_POS);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
	vec3 specular = specularStrength * spec * UNI_LIGHT_COLOR.xyz; 

	vec3 result = (ambient + diffuse + specular) * UNI_OBJECT_COLOR.xyz;

	LOCAL_COLOR = vec4(result, 1.0);
}