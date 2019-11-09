#version 130

in      vec3 in_position;
in      vec4 in_color;
out     vec4 ex_color;
uniform mat4 mvp;

void main(void)
{
    ex_color = in_color;
    gl_Position = mvp * vec4(in_position,1);
}
