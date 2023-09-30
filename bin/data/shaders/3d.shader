#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(a_Position, 1.0);
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 o_Color;

void main()
{
    o_Color = vec4(0.0, 0.5, 1.0, 1.0);
}

#shader geometry
#version 460 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

void main()
{
    for (int i = 0; i < 3; ++i)
    {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
        gl_Position = gl_in[(i + 1) % 3].gl_Position;
        EmitVertex();
        EndPrimitive();
    }
}