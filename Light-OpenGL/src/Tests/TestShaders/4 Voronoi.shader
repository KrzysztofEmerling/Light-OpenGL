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

vec2 random2(vec2 uv) {
    uv = vec2(dot(uv, vec2(127.1, 311.7)),
              dot(uv, vec2(269.5, 183.3)));
    return fract(sin(uv) * 43758.5453);
}

float voronoi(vec2 uv) {
    vec2 i_uv = floor(uv);   
    vec2 f_uv = fract(uv);  

    float m_dist = 1.0;       
    vec2 m_point;           


    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            vec2 neighbor = vec2(float(x), float(y));
            vec2 point = random2(i_uv + neighbor); 
            point = 0.5 + 0.5 * sin(point * u_Time); 

            vec2 diff = neighbor + point - f_uv;  
            float dist = length(diff);              

            if (dist < m_dist) {
                m_dist = dist;
                m_point = point;
            }
        }
    }

    return m_dist;
}

void main() {
    vec2 uv = v_TexCoord * 7.0; 
    uv.x *= u_Aspect;

    color = vec4(vec3(1.0) - vec3(voronoi(uv)), 1.0);
}
