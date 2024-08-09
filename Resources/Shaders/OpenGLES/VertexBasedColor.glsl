// INSERT COLOR BASED ON VERTEX

#type vertex
#version 300 es

// Vertex Shader
layout(location = 0) in vec3 ATTR_POS;
layout(location = 1) in vec4 ATTR_COLOR;

uniform mat4 UNI_VPM;
uniform mat4 UNI_MODELMAT;

out highp vec3 VAR_POS;
out mediump vec4 VAR_COLOR;

void main()
{
    VAR_POS = ATTR_POS;
    VAR_COLOR = ATTR_COLOR;
    gl_Position = UNI_VPM * UNI_MODELMAT * vec4(ATTR_POS, 1.0);
}

#type fragment
#version 300 es

// Fragment Shader
precision mediump float;

in highp vec3 VAR_POS;
in mediump vec4 VAR_COLOR;

layout(location = 0) out mediump vec4 color;

void main()
{
    // You can uncomment this if you need position-based coloring
    // color = vec4(VAR_POS * 0.5 + 0.5, 1.0);
    color = VAR_COLOR;
}
