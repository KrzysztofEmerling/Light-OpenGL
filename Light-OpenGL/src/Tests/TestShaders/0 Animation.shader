#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
    gl_Position = vec4(a_Position, 0.0, 1.0);

    v_TexCoord = a_TexCoord;
}

#shader fragment
#version 450 core

in vec2 v_TexCoord;

uniform float u_Time;
uniform float u_Aspect;

out vec4 color;

float random(vec2 uv) {
    return fract(sin(dot(uv.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

void main()
{
    vec2 uv = v_TexCoord * 10.0;
    uv.x *= u_Aspect;

    float value = sin(uv.x + u_Time) * cos(uv.y + u_Time);
    color = vec4(vec3(value), 1.0);
}
