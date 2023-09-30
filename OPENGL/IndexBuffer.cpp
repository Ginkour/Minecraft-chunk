#include "IndexBuffer.h"
#include "Utilities.h"
//unsigned int mge::IndexBuffer::currentIB = 0;
mge::IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count, mge::DrawType dt_tp)
    : m_Count(0), m_indexBufferID(0), initialized(false)
{
    if (count > 0)
    {
        InitBuffer(data, count, dt_tp);
    }
}

mge::IndexBuffer::~IndexBuffer()
{
    if (initialized)
        glDeleteBuffers(1, &m_indexBufferID);
}
void mge::IndexBuffer::InitBuffer(const unsigned int* data, const unsigned int count, mge::DrawType dt_tp)
{
    if (!initialized)
    {
        initialized = true;
        m_Count = count;
        drawType = dt_tp;
        glGenBuffers(1, &m_indexBufferID);
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, mge::getDrawType(dt_tp));
        Unbind();
    }
}
void mge::IndexBuffer::Update(const unsigned int* data, const unsigned int size, const unsigned int pos)
{
    if (initialized)
    {
        Bind();
        GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, pos, size, data));
    }
}
void mge::IndexBuffer::Bind() const
{
    if (initialized)
    {
        //if (m_indexBufferID != currentIB)
        //{
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
            //currentIB = m_indexBufferID;
        //}
    }
    else Unbind();
}

void mge::IndexBuffer::Unbind() const
{
    //currentIB = 0;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
