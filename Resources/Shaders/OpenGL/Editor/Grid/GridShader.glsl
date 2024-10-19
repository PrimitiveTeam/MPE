// GRID SHADER

#type vertex
#version 330 core

layout(location = 0) in vec3 ATTR_POS;
layout(location = 1) in vec3 ATTR_NORMALS;
layout(location = 2) in vec2 ATTR_TEXCOORD;

uniform mat4 UNI_VPM;
uniform mat4 UNI_MODELMAT;

void main()
{
    gl_Position = UNI_VPM * UNI_MODELMAT * vec4(ATTR_POS, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 LOCAL_COLOR;

uniform vec4 UNI_COLOR;

void main()
{
    // Light gray color
    // GRID_LINES_COLOR = vec4(0.75, 0.75, 0.75, 1.0);
    LOCAL_COLOR = UNI_COLOR;
}
