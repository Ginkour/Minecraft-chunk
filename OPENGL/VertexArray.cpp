#include "VertexArray.h"

mge::VertexArray::VertexArray() : m_vertexBufferID(0)
{
	glGenVertexArrays(1, &m_vertexBufferID);
}

mge::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vertexBufferID);
}

void mge::VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	m_VertexBufferLayout = layout;
	Bind();
	vb.Bind();
	SpecifyLayout();
	Unbind();
	//vb.Unbind();
}

void mge::VertexArray::SpecifyLayout()
{
	const std::vector<VertexBufferElement> elements = m_VertexBufferLayout.GetElements();
	uint64_t offset = 0;
	for (UINT64 i = 0; i < elements.size(); i++)
	{
		const VertexBufferElement& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type,
			element.normilized, m_VertexBufferLayout.GetStride(), (const void*)offset);

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void mge::VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_vertexBufferID));
}

void mge::VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
