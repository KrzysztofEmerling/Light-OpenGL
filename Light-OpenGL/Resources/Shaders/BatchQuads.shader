#shader vertex
#version 450 core

layout(location = 0) in vec4 position;

layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 color;
layout(location = 3) in float texID;

out vec2 v_TexCoord;
out float v_TexID;
out vec4 v_Color;

uniform mat4 u_MVP;

void main()
{
gl_Position = u_MVP * position;

v_TexCoord = texCoord;  
v_TexID = texID;
v_Color = color;

};

#shader fragment
#version 450 core

in vec2 v_TexCoord;
in float v_TexID;
in vec4 v_Color;

layout(location = 0) out vec4 color;

uniform sampler2D u_Texture [3]; 

void main()
{
vec4 texColor = texture(u_Texture[int(v_TexID)], v_TexCoord);
color = mix(texColor, v_Color, 0.5);
};