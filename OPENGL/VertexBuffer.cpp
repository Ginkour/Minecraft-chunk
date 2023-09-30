#include "VertexBuffer.h"
#include "Utilities.h"
//mge::UINT32 mge::VertexBuffer::currentVB = 0;
mge::VertexBuffer::VertexBuffer(const void* data, mge::UINT32 size, mge::DrawType dt_tp) :
	m_vertexBufferID(0), initialized(false), m_size(0), drawType(dt_tp)
{
	if (size > 0)
	{
		InitBuffer(data, size, dt_tp);
	}
}

mge::VertexBuffer::~VertexBuffer()
{
	if (initialized)
	{
		glDeleteBuffers(1, &m_vertexBufferID);
	}
}
void mge::VertexBuffer::InitBuffer(const void* data, mge::UINT32 size, mge::DrawType dt_tp)
{
	if (!initialized)
	{
		initialized = true;
		m_size = size;
		drawType = dt_tp;
		glGenBuffers(1, &m_vertexBufferID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, m_size, data, getDrawType(dt_tp));
		Unbind();
	}
}
void mge::VertexBuffer::Update(const void* data, const unsigned int size, const unsigned int pos)
{
	if (initialized)
	{
		Bind();
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
	}
}

void mge::VertexBuffer::Bind() const
{
	if (initialized)
	{
		//if (m_vertexBufferID != currentVB)
		//{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID));
		//	currentVB = m_vertexBufferID;
		//}
	}
	else Unbind();
}

void mge::VertexBuffer::Unbind() const
{
	//currentVB = 0;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
