#pragma once
#include "Utilities.h"
namespace mge 
{
	class vec2us
	{
	public:
		unsigned short x, y;
		vec2us(unsigned short _x = 0.f, unsigned short _y = 0.f) :x(_x), y(_y) {};
	public:
		void operator+=(vec2us& other);
		vec2us operator+(vec2us& other) const;
		void operator-=(vec2us& other);
		vec2us operator-(vec2us& other) const;
		bool operator==(vec2us& other) const;
	};
	class Vector2f
	{
	public: 
		FL32 x, y;
		Vector2f(FL32 _x = 0.f, FL32 _y = 0.f) :x(_x), y(_y) {};
	public:
		void operator+=(Vector2f& other);
		Vector2f operator+(Vector2f& other) const;
		void operator-=(Vector2f& other);
		Vector2f operator-(Vector2f& other) const;
		bool operator==(Vector2f& other) const;
	};
	class Vector2d
	{
	public:
		FL64 x, y;
		Vector2d(FL64 _x = 0.0, FL64 _y = 0.0) :x(_x), y(_y) {};
	public:
		void operator+=(Vector2d& other);
		Vector2d operator+(Vector2d& other) const;
		bool operator==(Vector2d& other) const;
	};
	class Vector2i
	{
	public:
		INT32 x, y;
		Vector2i(INT32 _x = 0, INT32 _y = 0) :x(_x), y(_y) {};
	public:
		void operator+=(Vector2i& other);
		Vector2i operator+(Vector2i& other) const;
		bool operator==(Vector2i& other) const;
	};
	class Vector2u
	{
	public:
		UINT32 x, y;
		Vector2u(UINT32 _x = 0, UINT32 _y = 0) :x(_x), y(_y) {};
	public:
		void operator+=(Vector2u& other);
		Vector2u operator+(Vector2u& other) const;
		bool operator==(Vector2u& other) const;
	};
	class Vector3f
	{
	public:
		FL32 x, y, z;
		Vector3f(FL32 _x = 0.f, FL32 _y = 0.f, FL32 _z = 0.f) :x(_x), y(_y), z(_z) {};
	public:
		void operator+=(Vector3f& other);
		Vector3f operator+(Vector3f& other) const;
		bool operator==(Vector3f& other) const;
	};
	class Vector3d
	{
	public:
		FL64 x, y, z;
		Vector3d(FL64 _x = 0.0, FL64 _y = 0.0, FL64 _z = 0.0) :x(_x), y(_y), z(_z) {};
	public:
		void operator+=(Vector3d& other);
		Vector3d operator+(Vector3d& other) const;
		bool operator==(Vector3d& other) const;
	};
	class Vector3i
	{
	public:
		INT32 x, y, z;
		Vector3i(INT32 _x = 0, INT32 _y = 0, INT32 _z = 0) :x(_x), y(_y), z(_z) {};
	public:
		void operator+=(Vector3i& other);
		Vector3i operator+(Vector3i& other) const;
		bool operator==(Vector3i& other) const;
	};
	class Vector3u
	{
	public:
		UINT32 x, y, z;
		Vector3u(UINT32 _x = 0, UINT32 _y = 0, UINT32 _z = 0) :x(_x), y(_y), z(_z) {};
	public:
		void operator+=(Vector3u& other);
		Vector3u operator+(Vector3u& other) const;
		bool operator==(Vector3u& other) const;
	};
	class Vector4f
	{
	public:
		FL32 x, y, z, t;
		Vector4f(FL32 _x = 0.f, FL32 _y = 0.f, FL32 _z = 0.f, FL32 _t = 0.0) :x(_x), y(_y), z(_z), t(_t) {};
	public:
		void operator+=(Vector4f& other);
		Vector4f operator+(Vector4f& other) const;
		bool operator==(Vector4f& other) const;
	};
	class Vector4d
	{
	public:
		FL64 x, y, z, t;
		Vector4d(FL64 _x = 0.0, FL64 _y = 0.0, FL64 _z = 0.0, FL64  _t = 0.0) :x(_x), y(_y), z(_z), t(_t) {};
	public:
		void operator+=(Vector4d& other);
		Vector4d operator+(Vector4d& other) const;
		bool operator==(Vector4d& other) const;
	};
	class Vector4i
	{
	public:
		INT32 x, y, z, t;
		Vector4i(INT32 _x = 0, INT32 _y = 0, INT32 _z = 0, INT32 _t = 0) :x(_x), y(_y), z(_z), t(_t) {};
	public:
		void operator+=(Vector4i& other);
		Vector4i operator+(Vector4i& other) const;
		bool operator==(Vector4i& other) const;
	};
	class Vector4u
	{
	public:
		UINT32 x, y, z, t;
		Vector4u(UINT32 _x = 0, UINT32 _y = 0, UINT32 _z = 0, UINT32 _t = 0) :x(_x), y(_y), z(_z), t(_t) {};
	public:
		void operator+=(Vector4u& other);
		Vector4u operator+(Vector4u& other) const;
		bool operator==(Vector4u& other) const;
	};
}

