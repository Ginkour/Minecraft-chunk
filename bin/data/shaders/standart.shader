#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_MVP;
uniform mat4 u_T;
void main()
{
	gl_Position = u_MVP * u_T * position;
	v_TexCoord = texCoord;
}
#shader fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
uniform vec4 u_C;
uniform sampler2D u_Texture;
void main()
{
    color = texture(u_Texture, v_TexCoord) * u_C;
}