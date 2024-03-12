#version 460 core

layout(location = 0) out vec4 o_Color;
in vec2 v_TexCoord;
// vec4 u_C;
layout(binding = 0)uniform sampler2D u_Texture;
void main()
{
    o_Color = texture(u_Texture, v_TexCoord);
}