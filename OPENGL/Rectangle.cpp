#include "Rectangle.h"

mge::Rectangle::Rectangle(mge::Shader* sh, mge::Texture* tex, mge::IndexBuffer* ib) :
    m_shader_p(sh), m_ib_p(ib), m_texture_p(tex), size(0.f, 0.f), origin(0.f, 0.f), pos(0.f), m_vb(vertices, sizeof(vertices), mge::DrawType::DYNAMIC), color(1.f, 1.f, 1.f, 1.f)
{
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(m_vb, layout);
}
void mge::Rectangle::setTexture(mge::Texture* texture)
{
    m_texture_p = texture;
}
void mge::Rectangle::setTextureRect(mge::uIntRect& rect)
{
    float y1 = 1.f - (float)rect.top / m_texture_p->getHeight();
    float x1 = (float)rect.left / m_texture_p->getWidth();
    float y2 = 1.f - (float)(rect.height + rect.top) / m_texture_p->getHeight();
    float x2 = (float)(rect.width + rect.left) / m_texture_p->getWidth();
    vertices[2] = x1; vertices[3] = y2;
    vertices[6] = x2; vertices[7] = y2;
    vertices[10] = x2; vertices[11] = y1;
    vertices[14] = x1; vertices[15] = y1;
    bufferUpdated = false;
}
void mge::Rectangle::setSize(mge::Vector2f _size)
{
	size = _size;
	recalc();
}

void mge::Rectangle::setAngle(float radians)
{
    angle = getInRange(radians);
    //angle = radians;
    transf.setAngle(angle);
}
void mge::Rectangle::setPos(mge::Vector2f _pos)
{
	pos = _pos;
	transf.setPosition(pos);
}
void mge::Rectangle::setOrigin(mge::Vector2f org)
{
	origin = org;
	recalc();
}
void mge::Rectangle::recalc()
{
    float y1 = -origin.y * size.y;
    float y2 = (1.f - origin.y) * size.y;
    float x1 = -origin.x * size.x;
    float x2 = (1.f - origin.x) * size.x;
    vertices[0] = x1; vertices[1] = y2;
    vertices[4] = x2; vertices[5] = y2;
    vertices[8] = x2; vertices[9] = y1;
    vertices[12] = x1; vertices[13] = y1;
    bufferUpdated = false;
}

