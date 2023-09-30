#pragma once
#include "Utilities.h"
#include <vector>
#include <stdexcept>
namespace mge 
{
    struct VertexBufferElement 
    {
        UINT32 type;
        UINT32 count;
        UINT8 normilized;
        static UINT32 GetSizeOfType(UINT32 type) 
        {
            switch (type)
            {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
            default:
                ASSERT(false);
                return 0;
            }
        }
    };
    class VertexBufferLayout
    {
    private:
        std::vector<mge::VertexBufferElement> m_Elements;
        UINT32 m_Stride;
    public:
        VertexBufferLayout();
        ~VertexBufferLayout();
        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="count">Number of things per line</param>
        template<typename T>
        void Push(UINT32 count)
        {
            throw std::runtime_error("Unsupported type in VertexBufferLayout");
        }
        template<>
        void Push<float>(UINT32 count)
        {
            m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
            m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
        }
        template<>
        void Push<UINT32>(UINT32 count)
        {
            m_Elements.push_back({ GL_UNSIGNED_INT,count, GL_FALSE });
            m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
        }
        template<>
        void Push<UINT8>(UINT32 count)
        {
            m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
            m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
        }
        inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
        inline UINT32 GetStride() const { return m_Stride; }
    };
}

