#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>
#endif

namespace gradient_shader
{
    std::string source = R"(
#version 120
const int num_points = 7;
vec2 points[num_points] = vec2[num_points](
    vec2(0, 0),
    vec2(400, 200),
    vec2(0, 620),
    vec2(530, 410),
    vec2(745, 235),
    vec2(1100, 0),
    vec2(1100, 620)
);
vec4 colors[num_points] = vec4[num_points](
    vec4(0.26, 0.15, 0.35, 1),
    vec4(0.0, 0.87, 1.0, 1),
    vec4(0.22, 0.33, 0.69, 1),
    vec4(0.93, 0.58, 1.0, 1),
    vec4(0.5, 0.68, 1.0, 1),
    vec4(0.45, 0.29, 0.43, 1),
    vec4(0.31, 0.18, 0.74, 1)
);
vec2 get_projection_distance(vec2 a, vec2 b, vec2 c) {
    float k2 = b.x*b.x - b.x*a.x + b.y*b.y -b.y*a.y;
    float k1 = a.x*a.x - b.x*a.x + a.y*a.y -b.y*a.y;
    float ab2 = (a.x - b.x)*(a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    float kcom = (c.x*(a.x - b.x) + c.y*(a.y-b.y));
    float d1 = (k1 - kcom) / ab2;
    float d2 = (k2 + kcom) / ab2;
    return vec2(d1, d2);
}
vec4 get_weighted_color_mix(vec4[num_points] colors, float[num_points] ratios){
    float r = 0;
    float g = 0;
    float b = 0;
    for (int i = 0; i < num_points; ++i) {
        r += colors[i].r * ratios[i];
        g += colors[i].g * ratios[i];
        b += colors[i].b * ratios[i];
    }
    return vec4(r, g, b, 1);
}
vec4 get_geometric_color_mix(vec2 p, vec2[num_points] points, vec4[num_points] colors) {
    float[num_points] color_ratios;
    for (int i = 0; i < num_points; ++i) {
        color_ratios[i] = 1;
    }
    for (int i1 = 0; i1 < num_points; ++i1) {
        for (int i2 = 0; i2 < num_points; ++i2) {
            if (i1 != i2) {
                vec2 d = get_projection_distance(points[i1], points[i2], p);
                color_ratios[i1] *= clamp(d[1], 0, 1);
            }
        }
    }
    float total_ratios_sum = 0;
    for (int i = 0; i < num_points; ++i) {
        total_ratios_sum += color_ratios[i];
    }
    for (int i = 0; i < num_points; ++i) {
        color_ratios[i] /= total_ratios_sum;
    }
    return get_weighted_color_mix(colors, color_ratios);
}
void main(void) {
    gl_FragColor = get_geometric_color_mix(vec2(gl_FragCoord.x, 620 - gl_FragCoord.y), points, colors);
}
)";
}