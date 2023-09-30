#pragma once
#include "Utilities.h"
#include "Container.h"
namespace mge 
{
	class Vertex
	{
	public:
		float Vertices[3];
		float Color[4];
		float TexCoord[2];
		float TextureSlot;
	public:
		inline void setX(float x)
		{
			Vertices[0] = x;
		}
		inline void setY(float y)
		{
			Vertices[1] = y;
		}
		inline void setZ(float z)
		{
			Vertices[2] = z;
		}
		inline void setColor(mge::Vector4f color)
		{
			Color[0] = color.x;
			Color[1] = color.y;
			Color[2] = color.z;
			Color[3] = color.t;
		}
		inline void setUV(float u, float v)
		{
			TexCoord[0] = u;
			TexCoord[1] = v;
		}
		inline void setTextureSlot(mge::INT32 texture_slot)
		{
			TextureSlot = static_cast<float>(texture_slot);
		}
	};

}

