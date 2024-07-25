// GRID SHADER

#type vertex
#version 330 core

layout(location = 0) in vec3 ATTR_POS;

uniform mat4 UNI_VPM;

void main()
{
    gl_Position = UNI_VPM * vec4(ATTR_POS, 1.0);
}

#type fragment
#version 330 core

out vec4 GRID_LINES_COLOR;

void main()
{
    // Light gray color
    GRID_LINES_COLOR = vec4(0.75, 0.75, 0.75, 1.0);
}
