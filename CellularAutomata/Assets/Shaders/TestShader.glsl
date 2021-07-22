#type vertex
#version 430 core

layout(location = 0) in vec3  a_Position;
layout(location = 1) in vec2  a_TexCoord;


out vec2 v_TexCoords;

layout(std140, binding = 0) uniform Camera
{
    mat4 u_ViewProjection;
    vec4 u_ViewPosition;
};


void main()
{
    v_TexCoords = a_TexCoord;
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}


#type fragment
#version 430

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoords;

layout(binding = 0) uniform sampler2D u_Texture;

void main()
{
    o_Color = texture(u_Texture, v_TexCoords);
}