// Light source with dynamic color

#type vertex
#version 330 core

layout(location = 0) in vec3 ATTR_POS;

uniform mat4 UNI_VPM;
uniform mat4 UNI_MODELMAT;

out vec3 VAR_POS;

void main()
{
	VAR_POS = ATTR_POS;
	gl_Position = UNI_VPM * UNI_MODELMAT * vec4(ATTR_POS, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 LOCAL_COLOR;

in vec3 VAR_POS;

uniform vec4 UNI_COLOR;

void main()
{
	LOCAL_COLOR = UNI_COLOR;
}