#pragma once
#include "typedefs.h"
#include "iostream"
#include "Utilities.h"
#include "Container.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <math.h>
#include <immintrin.h.>
namespace mge
{
	constexpr double _0PI = 0.0;				    //0/360 degrees
	constexpr double _PI = 3.14159265358979323846;	//  180 degrees
	constexpr double _PI_2 = _PI / 2.0;				//   90 degrees
	constexpr double _PI_3 = _PI / 3.0;				//   60 degrees
	constexpr double _PI_4 = _PI / 4.0;				//   45 degrees
	constexpr double _PI_6 = _PI / 6.0;				//   30 degrees
	constexpr double _2PI = 2.0 * _PI;				//  360 degrees
	constexpr double _3PI_2 = 3.0 * _PI_2;			//  270 degrees
	constexpr double _2PI_3 = 2.0 * _PI_3;			//  120 degrees
	constexpr float _0PIf = 0.f;				    //0/360 degrees
	constexpr float _PIf = (float)_PI;              //  180 degrees
	constexpr float _PI_2f = (float)_PI_2;			//   90 degrees
	constexpr float _PI_3f = (float)_PI_3;			//   60 degrees
	constexpr float _PI_4f = (float)_PI_4;			//   45 degrees
	constexpr float _PI_6f = (float)_PI_6;			//   30 degrees
	constexpr float _2PIf = (float)_2PI;			//  360 degrees
	constexpr float _3PI_2f = (float)_3PI_2;		//  270 degrees
	constexpr float _2PI_3f = (float)_2PI_3;		//  120 degrees
	inline float getInRange(float angle)
	{
		if (angle <= _PIf && angle >= -_PIf)
			return angle;
		else
		{
			bool sign = angle < 0.f;
			angle = Absf(angle);
			float full = (angle / _PIf);
			float whole = (float)((int)full);
			if (full < whole)
				angle -= whole * _PIf;
			else
				angle -= (whole + 1.f) * _PIf;
			if (sign)
				return -angle;
			else
				return angle;
		}
	}
	inline float Deg2Radf(float angle)
	{
		angle *= _PIf / 180.f;
		return getInRange(angle);
	}
	void SinCosf(float angle, float* sin, float* cos);
	inline float GetRandRangef(float min, float max)
	{
		static float sl1rm = 1.f / RAND_MAX;
		return min + (max - min) * sl1rm * rand();
	}
	namespace matrices 
	{
		const float identity4[4][4] = {
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		}; 
		const float zero4[4][4] = {
			0.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 0.f
		};
	}
	const enum class MatPreType
	{
		DATA,
		IDEN,
		ZERO,
		NONE
	};
	class Mat4
	{
	public:
		float m_mat[4][4];

		Mat4(MatPreType mpt = MatPreType::NONE, float** data = nullptr);
		const void operator = (float** other);
		const void operator = (float* other);
		const void operator = (Mat4& other);
		const mge::Mat4 operator * (Mat4& other); 
		const void operator *= (Mat4& other);
		const void setIdentity();
		const void setZero();
	};
	class Transform
	{
	public:
		Mat4 m_transfrom;
		mge::Vector2f position;
		float rotation;
	public:
		Transform(): m_transfrom(MatPreType::IDEN), position(0.f, 0.f), rotation(0.f){}
		void setPosition(mge::Vector2f pos);
		void setAngle(float radians);
	};
	class TransformCPU
	{
	public:
		Mat4 m_transfrom;
		mge::Vector2f position;
		bool updated = false;
	public:
		TransformCPU() : m_transfrom(MatPreType::IDEN), position(0.f, 0.f) {}
		void setPosition(mge::Vector2f pos);
		void move(mge::Vector2f pos);
		void setAngle(float radians);
	};

	void mult(Mat4& one, Mat4& other);
	void mult(Mat4& one, Mat4& other, Mat4& result);
	void setOrtho(Mat4& mat, float left, float right, float bottom, float top, float zNear, float zFar);
	static void vec2TT4(float* vec2, __m128* other_2columns)
	{
		// 32_it float registers
		__m128 result;
		// should be reworked using masking and blending 
		// current_row = _mm_loadu_ps(vec2);
		__m128 current_row = _mm_set_ps(1.f, 0.f, vec2[1], vec2[0]);
		for (unsigned int column = 0; column < 2; ++column)
		{
			result = _mm_mul_ps(current_row, other_2columns[column]);
			result = _mm_hadd_ps(result, result);
			result = _mm_hadd_ps(result, result);
			_mm_store_ss(&vec2[column], result);
		}
	};
	static void vec3TT4(float* vec3, __m128* other_3columns)
	{
		// 32_it float registers
		__m128 result;
		// should be reworked using masking and blending 
		// current_row = _mm_loadu_ps(vec2);
		__m128 current_row = _mm_set_ps(1.f, vec3[2], vec3[1], vec3[0]);
		for (unsigned int column = 0; column < 3; ++column)
		{
			result = _mm_mul_ps(current_row, other_3columns[column]);
			result = _mm_hadd_ps(result, result);
			result = _mm_hadd_ps(result, result);
			_mm_store_ss(&vec3[column], result);
		}
	};
}

