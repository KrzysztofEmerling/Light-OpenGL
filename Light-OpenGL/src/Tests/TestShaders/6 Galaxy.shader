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


float random(vec2 uv)
{
    const float a = 12.9898;
    const float b = 78.233;
    const float c = 43758.5453;
    
    float dt = dot(uv.xy, vec2(a, b));
    float sn = mod(dt, 3.14);
    return fract(sin(sn) * c);
}

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

float fbm(vec2 uv)
{
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


vec3 nebula(vec2 uv)
{
    float noise = smoothstep(0.025, 0.65,fbm(uv));   
    return vec3(noise);
}

float starsPosition(vec2 uv, float density)
{
    float noise = random(uv);
    return step(1.0 - density, noise); 
}

vec3 genGalaxy(vec2 uv)
{
    vec3 nebula = nebula(uv);
    vec2 stableUv = floor(uv * 600.0);  

    float density = clamp(step(0.08,nebula.x) / 500.0 + smoothstep(0.005, 0.75, nebula.x) / 270.0, 0.0005, 0.01);
    density *= 0.8;

    float star = starsPosition(stableUv, density);
    vec3 starColor = mix(vec3(1.0, 0.8, 0.6), vec3(0.6, 0.8, 1.0), random2(stableUv).x);
    nebula = nebula * vec3(1.0, 0.2, 0.8);

    return nebula + starColor * star;
}

vec3 blurBrightElements(vec2 uv, vec3 originalColor, float brightnessThreshold) {
    vec3 blurredColor = vec3(0.0);
    int samples = 0;

    // Sample neighboring colors (adjust the step size for the blur strength)
    for (int x = -4; x < 5; x++)
    {
        for (int y = -4; y < 5; y++)
        {
            vec2 offset = vec2(x, y) * 0.001; 
            
            vec2 sampleUV = uv + offset;
            
            vec3 sampleColor = genGalaxy(sampleUV); 

            blurredColor += sampleColor;
            samples++;
        }
    }

    blurredColor /= float(samples); 
    //blurredColor.y = 1.0;
    return mix(originalColor, blurredColor, step(brightnessThreshold, length(originalColor)));
}

void main() {
    vec2 uv = v_TexCoord * 0.7; 
    uv.x *= u_Aspect;
    uv += u_Time * 0.1;

    vec3 nebula = nebula(uv);
    vec2 stableUv = floor(uv * 600.0);  

    float density = clamp(step(0.08,nebula.x) / 500.0 + smoothstep(0.005, 0.75, nebula.x) / 270.0, 0.0005, 0.01);
    density *= 0.8;
    float star = starsPosition(stableUv, density);
    vec3 starColor = mix(vec3(1.0, 0.8, 0.6), vec3(0.6, 0.8, 1.0), random2(stableUv).x);
    nebula = nebula * vec3(1.0, 0.2, 0.8);

    vec3 stars = starColor * star;
    vec3 galaxy = clamp(nebula + stars, 0.0, 1.0);
    vec3 bluredGalaxy = blurBrightElements(uv, galaxy, 0.15);

    color = vec4(bluredGalaxy + stars, 1.0);
}


