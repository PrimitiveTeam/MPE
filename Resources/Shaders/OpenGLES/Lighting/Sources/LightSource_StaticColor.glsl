// Light source with a static color

#type vertex
#version 300 es

layout(location = 0) in vec3 ATTR_POS;

uniform mat4 UNI_VPM;
uniform mat4 UNI_MODELMAT;

out highp vec3 VAR_POS;

void main()
{
	VAR_POS = ATTR_POS;
	gl_Position = UNI_VPM * UNI_MODELMAT * vec4(ATTR_POS, 1.0);
}

#type fragment
#version 300 es

precision mediump float;
precision mediump int;

out mediump vec4 LOCAL_COLOR;

in highp vec3 VAR_POS;

void main()
{
	LOCAL_COLOR = vec4(1.0f);
}