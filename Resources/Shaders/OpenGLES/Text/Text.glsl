#type vertex
#version 300 es

// <vec2 pos, vec2 tex>
layout (location = 0) in vec4 UNI_TEXTURE_COORDS;
uniform mat4 UNI_PROJECTION_MATRIX;

out vec2 VAR_TEXTURE_COORDS;

void main()
{
    gl_Position = UNI_PROJECTION_MATRIX * vec4(UNI_TEXTURE_COORDS.xy, 0.0, 1.0);
    VAR_TEXTURE_COORDS = UNI_TEXTURE_COORDS.zw;
}

#type fragment
#version 300 es

precision mediump float;
precision mediump int;

in vec2 VAR_TEXTURE_COORDS;
out vec4 color;

uniform sampler2D UNI_TEXT;
uniform vec4 UNI_TEXT_COLOR;

void main()
{
    float alpha = texture(UNI_TEXT, VAR_TEXTURE_COORDS).r;
    color = vec4(UNI_TEXT_COLOR.rgb, UNI_TEXT_COLOR.a * alpha);
}