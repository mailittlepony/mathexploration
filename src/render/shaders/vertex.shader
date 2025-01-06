
#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex_coord;

out vec2 tex_coord;

uniform mat4 projection;
uniform mat4 view;
uniform sampler2D texture1;
uniform sampler2D texture2; // Second texture

void main()
{
    gl_Position = projection * view * vec4(a_pos, 1.0);
    tex_coord = a_tex_coord;
}
