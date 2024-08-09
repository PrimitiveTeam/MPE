// BASIC TEXTURE SHADER

#type vertex
#version 300 es

// Vertex Shader
layout(location = 0) in vec3 ATTR_POS;
layout(location = 1) in vec2 ATTR_TEXCOORD;

uniform mat4 UNI_VPM;
uniform mat4 UNI_MODELMAT;

out highp vec2 VAR_TEXCOORD;

void main()
{
    VAR_TEXCOORD = ATTR_TEXCOORD;
    gl_Position = UNI_VPM * UNI_MODELMAT * vec4(ATTR_POS, 1.0);
}

#type fragment
#version 300 es

// Fragment Shader
precision mediump float;

in highp vec2 VAR_TEXCOORD;

uniform sampler2D UNI_TEXTURE;

layout(location = 0) out mediump vec4 LOCAL_COLOR;

void main()
{
    LOCAL_COLOR = texture(UNI_TEXTURE, VAR_TEXCOORD);
}
