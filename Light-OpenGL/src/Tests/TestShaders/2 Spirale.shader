#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
    vec2 scaledPosition = a_Position;
    gl_Position = vec4(a_Position, 0.0, 1.0);

    v_TexCoord = a_TexCoord;
}

#shader fragment
#version 450 core

in vec2 v_TexCoord;

uniform float u_Aspect;
uniform float u_Time;

out vec4 color;

vec2 randomGradient(vec2 point)
{
    point = point + 0.01;
    float x = dot(point, vec2(123.4, 234.5));
    float y = dot(point, vec2(234.5, 345.6));
    vec2 gradient = vec2(x,y);
    gradient = sin(gradient);
    gradient = gradient * 43758.5453;

    gradient = sin(gradient + u_Time);
    return gradient;
}
vec2 quintic(vec2 uv)
{
    uv = uv * uv * uv * (uv * (uv * 6.0 - 15.0) + 10.0);
    return uv;
}
float perlinNoise(vec2 uv)
{
    vec2 gridId = floor(uv);
    vec2 gridUv = fract(uv);

    vec2 gridBl = randomGradient(gridId + vec2(0.0,0.0));
    vec2 gridBr = randomGradient(gridId + vec2(1.0,0.0));
    vec2 gridTr = randomGradient(gridId + vec2(1.0,1.0));
    vec2 gridTl = randomGradient(gridId + vec2(0.0,1.0));

    vec2 distToBl = gridUv - vec2(0.0,0.0);
    vec2 distToBr = gridUv - vec2(1.0,0.0);
    vec2 distToTr = gridUv - vec2(1.0,1.0);
    vec2 distToTl = gridUv - vec2(0.0,1.0);

    float dotBl = dot(gridBl, distToBl);
    float dotBr = dot(gridBr, distToBr);
    float dotTr = dot(gridTr, distToTr);
    float dotTl = dot(gridTl, distToTl);

    gridUv = quintic(gridUv);

    float bottom = mix(dotBl,dotBr, gridUv.x);
    float top = mix(dotTl,dotTr, gridUv.x);
    return mix(bottom,top, gridUv.y);   
}

void main() {
    vec2 uv = v_TexCoord.xy * 10 - 0.5;
    uv.x *= u_Aspect;

    float angle = atan(uv.y, uv.x);
    float radius = length(uv);
    float mandala = sin(6.0 * angle + radius * 10.0 + u_Time);
    color = vec4(vec3(0.8, 0.2, 0.5) * mandala, 1.0);
}