#include "Container.h"
//vec2 unsigned short
void mge::vec2us::operator+=(vec2us& other)
{
	x += other.x;
	y += other.y;
}
mge::vec2us mge::vec2us::operator+(vec2us& other) const
{
	return vec2us(x + other.x, y + other.y);
}
void mge::vec2us::operator-=(vec2us& other)
{
	x -= other.x;
	y -= other.y;
}
mge::vec2us mge::vec2us::operator-(vec2us& other) const
{
	return vec2us(x - other.x, y - other.y);
}
bool mge::vec2us::operator==(vec2us& other) const
{
	return (x == other.x && y == other.y);
}
//Vector 2f
void mge::Vector2f::operator+=(Vector2f& other)
{
	x += other.x;
	y += other.y;
}
mge::Vector2f mge::Vector2f::operator+(Vector2f& other) const
{
	return Vector2f(x + other.x, y + other.y);
}
void mge::Vector2f::operator-=(Vector2f& other)
{
	x -= other.x;
	y -= other.y;
}
mge::Vector2f mge::Vector2f::operator-(Vector2f& other) const
{
	return Vector2f(x - other.x, y - other.y);
}
bool mge::Vector2f::operator==(Vector2f& other) const
{
	return (x == other.x && y == other.y);
}
//Vector 2d
void mge::Vector2d::operator+=(Vector2d& other)
{
	x += other.x;
	y += other.y;
}
mge::Vector2d mge::Vector2d::operator+(Vector2d& other) const
{
	return Vector2d(x + other.x, y + other.y);
}
bool mge::Vector2d::operator==(Vector2d& other) const
{
	return (x == other.x && y == other.y);
}
//Vector 2i
void mge::Vector2i::operator+=(Vector2i& other)
{
	x += other.x;
	y += other.y;
}
mge::Vector2i mge::Vector2i::operator+(Vector2i& other) const
{
	return Vector2i(x + other.x, y + other.y);
}
bool mge::Vector2i::operator==(Vector2i& other) const
{
	return (x == other.x && y == other.y);
}
//Vector 2u
void mge::Vector2u::operator+=(Vector2u& other)
{
	x += other.x;
	y += other.y;
}
mge::Vector2u mge::Vector2u::operator+(Vector2u& other) const
{
	return Vector2u(x + other.x, y + other.y);
}
bool mge::Vector2u::operator==(Vector2u& other) const
{
	return (x == other.x && y == other.y);
}
//Vector 3f
void mge::Vector3f::operator+=(Vector3f& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}
mge::Vector3f mge::Vector3f::operator+(Vector3f& other) const
{
	return Vector3f(x + other.x, y + other.y, z + other.z);
}
bool mge::Vector3f::operator==(Vector3f& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}
//Vector 3d
void mge::Vector3d::operator+=(Vector3d& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}
mge::Vector3d mge::Vector3d::operator+(Vector3d& other) const
{
	return Vector3d(x + other.x, y + other.y, z + other.z);
}
bool mge::Vector3d::operator==(Vector3d& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}
//Vector 3i
void mge::Vector3i::operator+=(Vector3i& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}
mge::Vector3i mge::Vector3i::operator+(Vector3i& other) const
{
	return Vector3i(x + other.x, y + other.y, z + other.z);
}
bool mge::Vector3i::operator==(Vector3i& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}
//Vector 3u
void mge::Vector3u::operator+=(Vector3u& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}
mge::Vector3u mge::Vector3u::operator+(Vector3u& other) const
{
	return Vector3u(x + other.x, y + other.y, z + other.z);
}
bool mge::Vector3u::operator==(Vector3u& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}
//Vector 4f
void mge::Vector4f::operator+=(Vector4f& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	t += other.t;
}
mge::Vector4f mge::Vector4f::operator+(Vector4f& other) const
{
	return Vector4f(x + other.x, y + other.y, z + other.z, t + other.t);
}
bool mge::Vector4f::operator==(Vector4f& other) const
{
	return (x == other.x && y == other.y && z == other.z && t == other.t);
}
//Vector 4d
void mge::Vector4d::operator+=(Vector4d& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	t += other.t;
}
mge::Vector4d mge::Vector4d::operator+(Vector4d& other) const
{
	return Vector4d(x + other.x, y + other.y, z + other.z, t + other.t);
}
bool mge::Vector4d::operator==(Vector4d& other) const
{
	return (x == other.x && y == other.y && z == other.z && t == other.t);
}
//Vector 4i
void mge::Vector4i::operator+=(Vector4i& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	t += other.t;
}
mge::Vector4i mge::Vector4i::operator+(Vector4i& other) const
{
	return Vector4i(x + other.x, y + other.y, z + other.z, t + other.t);
}
bool mge::Vector4i::operator==(Vector4i& other) const
{
	return (x == other.x && y == other.y && z == other.z && t == other.t);
}
//Vector 4u
void mge::Vector4u::operator+=(Vector4u& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	t += other.t;
}
mge::Vector4u mge::Vector4u::operator+(Vector4u& other) const
{
	return Vector4u(x + other.x, y + other.y, z + other.z, t + other.t);
}
bool mge::Vector4u::operator==(Vector4u& other) const
{
	return (x == other.x && y == other.y && z == other.z && t == other.t);
}