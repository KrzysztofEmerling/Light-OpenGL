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

vec2 random2(vec2 uv)
{
    uv = vec2(dot(uv, vec2(127.1, 311.7)),
              dot(uv, vec2(269.5, 183.3)));
    return fract(sin(uv) * 43758.5453);
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

    vec2 gridBl = random2(gridId + vec2(0.0,0.0));
    vec2 gridBr = random2(gridId + vec2(1.0,0.0));
    vec2 gridTr = random2(gridId + vec2(1.0,1.0));
    vec2 gridTl = random2(gridId + vec2(0.0,1.0));

    vec2 distToBl = gridUv - vec2(0.0,0.0);
    vec2 distToBr = gridUv - vec2(1.0,0.0);
    vec2 distToTr = gridUv - vec2(1.0,1.0);
    vec2 distToTl = gridUv - vec2(0.0,1.0);

    float dotBl = dot(gridBl, distToBl);
    float dotBr = dot(gridBr, distToBr);
    float dotTr = dot(gridTr, distToTr);
    float dotTl = dot(gridTl, distToTl);

    gridUv = quintic(gridUv);
    vec2 u = gridUv * gridUv * (3.0 - 2.0 * gridUv);
    

    float bottom = mix(dotBl, dotBr, u.x);
    float top = mix(dotTl, dotTr, u.x);
    return mix(bottom, top, u.y);   
}

float fbm(vec2 uv) {
    float value = 0.0;
    float amplitude = 0.5;
    float frequency = 1.0;
    for (int i = 0; i < 5; i++) {
        value += amplitude * perlinNoise(uv * frequency);
        frequency *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}


void main() {
    vec2 uv = v_TexCoord; 
    uv.x *= u_Aspect;
    float fractal_nois = smoothstep(0.025, 0.7,fbm(uv + u_Time * 0.1));
    color = vec4(vec3(fractal_nois), 1.0);
}