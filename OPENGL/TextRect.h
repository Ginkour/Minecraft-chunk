#pragma once
#include "Utilities.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Texture.h"
namespace mge 
{
	struct Quad 
	{
		mge::Vertex m_vertices[4];
	};
	static void setTextRectSize(mge::Quad& m_quad, float x, float y)
	{
		m_quad.m_vertices[0].setX(0.f); m_quad.m_vertices[0].setY(y  ); m_quad.m_vertices[0].setZ(0.f);
		m_quad.m_vertices[1].setX(x );  m_quad.m_vertices[1].setY(y  ); m_quad.m_vertices[1].setZ(0.f);
		m_quad.m_vertices[2].setX(x );  m_quad.m_vertices[2].setY(0.f); m_quad.m_vertices[2].setZ(0.f);
		m_quad.m_vertices[3].setX(0.f); m_quad.m_vertices[3].setY(0.f); m_quad.m_vertices[3].setZ(0.f);
	}
	static void setTextRectSize(mge::Quad& m_quad, float x)
	{
		setTextRectSize(m_quad, x, x);
	}
	static void setTextRectTextureRect(mge::Quad& m_quad, mge::uIntRect* rect, mge::Texture& texture)
	{
		float y1;
		float x1;
		float y2;
		float x2;
		if (rect)
		{
			mge::Vector2f texture_size((float)texture.getWidth(), (float)texture.getHeight());
			y1 = 1.f - ((float)rect->top / texture_size.y);
			x1 = (float)rect->left / texture_size.x;
			y2 = 1.f - ((float)(rect->height + rect->top) / texture_size.y);
			x2 = (float)(rect->width + rect->left) / texture_size.x;
		}
		else 
		{
			y1 = 0.f;
			x1 = 0.f;
			y2 = 1.f;
			x2 = 1.f;
		}
		m_quad.m_vertices[0].setUV(x1, y2);
		m_quad.m_vertices[1].setUV(x2, y2);
		m_quad.m_vertices[2].setUV(x2, y1);
		m_quad.m_vertices[3].setUV(x1, y1);
	}
	static void setTextRectColor(mge::Quad& m_quad, mge::Vector4f color)
	{
		for (int i = 0; i < 4; i++)
			m_quad.m_vertices[i].setColor(color);
	}
	static void setTextRectTextureSlot(mge::Quad& m_quad, mge::INT32 slot)
	{
		for (int i = 0; i < 4; i++)
			m_quad.m_vertices[i].setTextureSlot(slot);
	}
	static void TextRectTransform(mge::Quad& m_quad, mge::TransformCPU& transform)
	{
		// transform CPU means columns are stored in raw(Transposed so can be loaded using mmloadups)
		__m128 transform_coulmns[2];
		for (unsigned int i = 0; i < 2; ++i)
			//m_mat[4][4] float array
			transform_coulmns[i] = _mm_loadu_ps(&transform.m_transfrom.m_mat[i][0]);
		for(unsigned int i = 0; i < 4; ++i)
			mge::vec2TT4(m_quad.m_vertices[i].Vertices, transform_coulmns);
	}
}
