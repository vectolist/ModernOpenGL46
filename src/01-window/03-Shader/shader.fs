#version 460 core

out vec4 outColor;

void main(){
    vec2 uv = gl_FragCoord.xy / vec2(500,500);
    outColor = vec4(uv, 1, 1);
    //outColor = vec4(vec3(gl_FragCoord.z), 1);
};