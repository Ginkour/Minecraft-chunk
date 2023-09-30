#pragma once
#include "Utilities.h"
#include "Container.h"
#include "Matrix.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
namespace mge 
{
    class Rectangle
    {
    public:
        mge::Shader* m_shader_p;
        mge::IndexBuffer* m_ib_p;
        mge::Texture* m_texture_p;


        mge::Vector4f color;
        mge::VertexArray va;
        VertexBuffer m_vb;
        // x  y  u  v
        // 0  1  2  3
        // 4  5  6  7
        // 8  9 10 11
        //12 13 14 15
        float vertices[16] =
        {
             0.f, 0.f, 0.f, 0.f, //0  left   bottom
             0.f, 0.f, 1.f, 0.f, //1  right  bottom
             0.f, 0.f, 1.f, 1.f, //2  right  top
             0.f, 0.f, 0.f, 1.f, //3  left   top
        };
        mge::Vector2f size;
        mge::Vector2f origin;
        mge::Vector2f pos;
        mge::Transform transf;
        float angle = 0.f;
        bool bufferUpdated = true;
        bool transformUpdated = true;
    public:
        Rectangle(mge::Shader* sh, mge::Texture* tex, mge::IndexBuffer* ib);
        inline void setShader(mge::Shader* sh) { m_shader_p = sh; };
        inline void setIB(mge::IndexBuffer* ib) { m_ib_p = ib; };
        void setTexture(mge::Texture* texture);
        void setTextureRect(mge::uIntRect& texture);
        void setSize(mge::Vector2f size);
        inline void setSize(float x, float y) { setSize({ x, y }); };
        void setAngle(float radians);
        void setPos(mge::Vector2f _pos);
        void setOrigin(mge::Vector2f pos);
        inline const mge::Vector2f getSize() const
        {
            return size;
        };
        inline const mge::Vector2f getOrigin() const
        {
            return origin;
        };
        inline const mge::Vector2f getPosition() const
        {
            return pos;
        };
        inline const void Rotate(float value_rad)
        {
            setAngle(angle + value_rad);
        }
        inline const void move(mge::Vector2f mov)
        {
            setPos(pos + mov);
        };
    private:
        void recalc();
    };
}

