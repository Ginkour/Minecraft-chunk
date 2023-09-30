#version 460 core
struct vec3ub 
{
    uint x;
    uint y;
    uint z;
};
layout(location = 0) in uint a_x;
layout(location = 1) in uint a_y;
layout(location = 2) in uint a_z;
layout(location = 3) in uint a_tX;
layout(location = 4) in uint a_tY;

out vec2 v_TexCoord;
uniform vec3 chunkPosition;

void main()
{
    v_TexCoord = a_TexCoord;
}