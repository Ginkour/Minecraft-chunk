#pragma once
#include "Utilities.h"
#include "typedefs.h"
namespace mge 
{
	class VertexBuffer
	{
	private:
		bool initialized;
		// The maximum number bytes
		mge::UINT32 m_size;
		// OpenGL internal ID
		mge::UINT32 m_vertexBufferID;
		mge::DrawType drawType;
		//static mge::UINT32 currentVB; 
	public:
		VertexBuffer(const void* data = nullptr, mge::UINT32 size = 0, mge::DrawType dt_tp = mge::DrawType::STATIC);
		~VertexBuffer();
		void InitBuffer(const void* data, const mge::UINT32 size, mge::DrawType dt_tp);
		//void Reallocate();
		inline mge::UINT32 getSize() { return m_size; };
		void Update(const void* data, const unsigned int size, const unsigned int pos = 0);
		void Bind() const;
		void Unbind() const;
	};
}

