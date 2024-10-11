// SPHERE SHADER


#type vertex
#version 330 core

layout(location = 0) in vec3 ATTR_POS;      // vertex position
layout(location = 1) in vec3 ATTR_NORMAL;   // vertex normal
layout(location = 2) in vec2 ATTR_TEXCOORD; // texture coordinates

uniform mat4 UNI_VPM;      // View-Projection Matrix
uniform mat4 UNI_MODELMAT; // Model Matrix
uniform mat4 UNI_NORMALMAT; // Normal Matrix

out vec3 VAR_VERTEX;   // Eye-space vertex position
out vec3 VAR_NORMAL;   // Transformed normal
out vec2 VAR_TEXCOORD; // Texture coordinates

void main()
{
    vec4 worldPosition = UNI_MODELMAT * vec4(ATTR_POS, 1.0);  // Transform vertex position to world space
    VAR_VERTEX = vec3(worldPosition);                         // Pass world space position to the fragment shader
    VAR_NORMAL = mat3(UNI_NORMALMAT) * ATTR_NORMAL;           // Transform normal to eye-space
    VAR_TEXCOORD = ATTR_TEXCOORD;                             // Pass texture coordinates

    gl_Position = UNI_VPM * worldPosition;                    // Final position using view-projection matrix
}

#type fragment
#version 330 core

layout(location = 0) out vec4 LOCAL_COLOR;

in vec3 VAR_VERTEX;   // Eye-space vertex position
in vec3 VAR_NORMAL;   // Transformed normal
in vec2 VAR_TEXCOORD; // Texture coordinates

uniform vec4 UNI_LIGHTPOS;       // Light position
uniform vec4 UNI_LIGHTAMBIENT;   // Light ambient color
uniform vec4 UNI_LIGHTDIFFUSE;   // Light diffuse color
uniform vec4 UNI_LIGHTSPECULAR;  // Light specular color
uniform vec4 UNI_MATERIALAMBIENT; // Material ambient color
uniform vec4 UNI_MATERIALDIFFUSE; // Material diffuse color
uniform vec4 UNI_MATERIALSPECULAR; // Material specular color
uniform float UNI_MATERIALSHININESS; // Material shininess
uniform sampler2D UNI_MAP0;      // Texture map
uniform bool UNI_TEXTUREUSED;    // Flag for texture usage

void main()
{
    vec3 normal = normalize(VAR_NORMAL);       // Normalize the normal
    vec3 lightDir;

    if (UNI_LIGHTPOS.w == 0.0)
    {
        lightDir = normalize(UNI_LIGHTPOS.xyz);  // Directional light
    }
    else
    {
        lightDir = normalize(UNI_LIGHTPOS.xyz - VAR_VERTEX);  // Point light
    }

    vec3 viewDir = normalize(-VAR_VERTEX);                  // Viewing direction
    vec3 reflectDir = reflect(-lightDir, normal);           // Reflection direction

    // Ambient component
    vec3 color = UNI_LIGHTAMBIENT.rgb * UNI_MATERIALAMBIENT.rgb;

    // Diffuse component
    float diff = max(dot(normal, lightDir), 0.0);
    color += UNI_LIGHTDIFFUSE.rgb * UNI_MATERIALDIFFUSE.rgb * diff;

    // Texture component
    if (UNI_TEXTUREUSED)
        color *= texture(UNI_MAP0, VAR_TEXCOORD).rgb;

    // Specular component
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), UNI_MATERIALSHININESS);
    color += UNI_LIGHTSPECULAR.rgb * UNI_MATERIALSPECULAR.rgb * spec;

    // Final output color
    LOCAL_COLOR = vec4(color, UNI_MATERIALDIFFUSE.a);
}
