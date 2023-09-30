#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
namespace mge 
{
	class VertexArray
	{
	private:
		UINT32 m_vertexBufferID;
		VertexBufferLayout m_VertexBufferLayout;
	public:
		VertexArray();
		~VertexArray();
		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		void SpecifyLayout();
		void Bind() const;
		void Unbind() const;
	};
}

