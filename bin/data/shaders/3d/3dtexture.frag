#version 460 core

layout(location = 0) out vec4 o_Color;
in vec2 v_TexCoord;
uniform vec4 u_C;
uniform sampler2D u_Texture;
void main()
{
    o_Color = texture(u_Texture, v_TexCoord);
    if(o_Color.w <= 0.5f)
    discard;
}