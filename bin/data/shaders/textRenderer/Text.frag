#version 460 core
layout(location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Texture;
void main()
{
	int index = int(v_TexIndex);
	if(index >= 0)
	{
		o_Color = texture(u_Texture, v_TexCoord) * v_Color;
	}
	else
	{
		o_Color = v_Color;
	}
}