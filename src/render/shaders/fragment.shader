
#version 330 core
out vec4 frag_color;
  
in vec2 tex_coord;

uniform sampler2D texture1;

void main()
{
    float r = texture(texture1, tex_coord).r;

    if (r > 0.9)
    {
        discard;
    }

    frag_color = vec4(r, r, r, 1.0);
}
