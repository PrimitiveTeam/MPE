// FLAT COLOR WITH LIGHTING

#type vertex
#version 300 es

layout(location = 0) in vec3 ATTR_POS;
layout(location = 1) in vec3 ATTR_NORMAL;

uniform mat4 UNI_VPM;
uniform mat4 UNI_MODELMAT;

out highp vec3 VAR_POS;
out highp vec3 VAR_NORMAL;
out highp vec3 VAR_FRAG_POS;

void main()
{
	VAR_POS = ATTR_POS;
	VAR_FRAG_POS = vec3(UNI_MODELMAT * vec4(ATTR_POS, 1.0));
	// TODO: The below is a costly operation and should be done on the CPU
	VAR_NORMAL = mat3(transpose(inverse(UNI_MODELMAT))) * ATTR_NORMAL;
	gl_Position = UNI_VPM * UNI_MODELMAT * vec4(ATTR_POS, 1.0);
}

#type fragment
#version 300 es

precision mediump float;
precision mediump int;

out mediump vec4 LOCAL_COLOR;

in highp vec3 VAR_POS;
in highp vec3 VAR_NORMAL;
in highp vec3 VAR_FRAG_POS;

uniform mediump vec4 UNI_OBJECT_COLOR;
uniform mediump vec4 UNI_LIGHT_COLOR;
uniform mediump vec3 UNI_LIGHT_POSITION;
uniform mediump vec3 UNI_VIEW_POSITION;

void main()
{
	// AMBIENT

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * UNI_LIGHT_COLOR.xyz;


	// DIFFUSE

	vec3 norm = normalize(VAR_NORMAL);
	vec3 lightDir = normalize(UNI_LIGHT_POSITION - VAR_FRAG_POS);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * UNI_LIGHT_COLOR.xyz;

	// SPECULAR

	float specularStrength = 0.5;
	vec3 viewDir = normalize(UNI_VIEW_POSITION - VAR_POS);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128.0);
	vec3 specular = specularStrength * spec * UNI_LIGHT_COLOR.xyz; 

	vec3 result = (ambient + diffuse + specular) * UNI_OBJECT_COLOR.xyz;

	LOCAL_COLOR = vec4(result, 1.0);
}