#pragma once
#include "Utilities.h"
#include "typedefs.h"
namespace mge 
{
	class IndexBuffer
	{
	private:
		bool initialized;
		// OpenGL internal ID
		unsigned int m_indexBufferID;
		// The maximum number of idecies, not the bytes
		unsigned int m_Count;
		//static unsigned int currentIB;
		mge::DrawType drawType;
	public:
		IndexBuffer(
			const unsigned int* data = nullptr,
			const unsigned int count = 0,
			mge::DrawType dt_tp = mge::DrawType::STATIC);
		~IndexBuffer();
		void InitBuffer(
			const unsigned int* data, 
			unsigned int count,
			mge::DrawType dt_tp);
		void Update(
			const unsigned int* data, 
			const unsigned int size, 
			const unsigned int pos = 0);
		void Bind() const;
		void Unbind() const;
		inline unsigned int GetCount() 
			const { return m_Count; }
	};
}

