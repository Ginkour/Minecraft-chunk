#include "Matrix.h"

void mge::setOrtho(Mat4& mat, float left, float right, float bottom, float top, float zNear, float zFar)
{
	mat.m_mat[0][0] = 2.f / (right - left);
	mat.m_mat[1][1] = 2.f / (top - bottom);
	mat.m_mat[2][2] = -2.f / (zFar - zNear);
	mat.m_mat[3][0] = -(right + left) / (right - left);
	mat.m_mat[3][1] = -(top + bottom) / (top - bottom);
	mat.m_mat[3][2] = -(zFar + zNear) / (zFar - zNear);
}

void mge::SinCosf(float angle, float* sin, float* cos)
{
	const float angle_sq = angle * angle;
	float SeriesElementX = angle * angle_sq * -0.16666667f;
	float SeriesElementY = angle_sq * -0.5f;
	*sin = angle + SeriesElementX;
	*cos = 1.f + SeriesElementY;
	for (unsigned int i = 2; i <= 6; ++i)
	{
		unsigned int b = 2 * i;
		SeriesElementX *= -1 * (angle_sq / (b * (b + 1)));
		SeriesElementY *= -1 * (angle_sq / (b * (b - 1)));
		*sin += SeriesElementX;
		*cos += SeriesElementY;
	}
}

void mge::mult(Mat4& one, Mat4& other)
{
	// 32_it float registers
	__m128 current_row, result, other_column[4];
	for (unsigned int i = 0; i < 4; ++i)
		other_column[i] = _mm_set_ps(other.m_mat[3][i], other.m_mat[2][i], other.m_mat[1][i], other.m_mat[0][i]);
	for (unsigned int row = 0; row < 4; ++row)
	{
		current_row = _mm_loadu_ps(&one.m_mat[row][0]); 
		for (unsigned int column = 0; column < 4; ++column)
		{
			result = _mm_mul_ps(current_row, other_column[column]);
			result = _mm_hadd_ps(result, result);
			result = _mm_hadd_ps(result, result);
			_mm_store_ss(&one.m_mat[row][column], result);
		}
	}
}

void mge::mult(Mat4& one, Mat4& other, Mat4& result)
{
	result = one;
	mult(result, other);
}

mge::Mat4::Mat4(MatPreType mpt, float** data)
{
	switch (mpt)
	{
	case mge::MatPreType::DATA:
		*this = data;
		break;
	case mge::MatPreType::IDEN:
		setIdentity();
		break;
	case mge::MatPreType::ZERO:
		setZero();
		break;
	default:
		return;
	}
}

const void mge::Mat4::operator=(float** other)
{
	for (unsigned int row = 0; row < 4; ++row)
		for (unsigned int column = 0; column < 4; ++column)
			m_mat[row][column] = other[row][column];
}
const void mge::Mat4::operator = (float* other)
{
	for (unsigned int row = 0; row < 4; ++row)
		for (unsigned int column = 0; column < 4; ++column)
			m_mat[row][column] = other[row * 4 + column];
}

const void mge::Mat4::operator=(Mat4& other)
{
	for (unsigned int row = 0; row < 4; ++row)
		for (unsigned int column = 0; column < 4; ++column)
			m_mat[row][column] = other.m_mat[row][column];
}

const mge::Mat4 mge::Mat4::operator*(Mat4& other)
{
	mge::Mat4 newmat(mge::MatPreType::NONE);
	mult(*this, other, newmat);
	return newmat;
}
const void mge::Mat4::operator*=(Mat4& other)
{
	mge::Mat4 newmat(mge::MatPreType::NONE);
	mult(*this, other);
}

const void mge::Mat4::setIdentity()
{
	for (unsigned int row = 0; row < 4; ++row)
		for (unsigned int column = 0; column < 4; ++column)
			m_mat[row][column] = matrices::identity4[row][column];
}

const void mge::Mat4::setZero()
{
	for (unsigned int row = 0; row < 4; ++row)
		for (unsigned int column = 0; column < 4; ++column)
			m_mat[row][column] = matrices::zero4[row][column];
}

void mge::Transform::setPosition(mge::Vector2f pos)
{
	m_transfrom.m_mat[3][0] = pos.x;
	m_transfrom.m_mat[3][1] = pos.y;
}

void mge::Transform::setAngle(float radians)
{
	float sin, cos;
	//sin = sinf(radians);
	//cos = cosf(radians);
	mge::SinCosf(radians, &sin, &cos);
	m_transfrom.m_mat[0][0] = cos;
	m_transfrom.m_mat[0][1] = -sin;
	m_transfrom.m_mat[1][0] = sin;
	m_transfrom.m_mat[1][1] = cos;
}
void mge::TransformCPU::setPosition(mge::Vector2f pos)
{
	m_transfrom.m_mat[0][3] = pos.x;
	m_transfrom.m_mat[1][3] = pos.y;
	updated = false;
}
void mge::TransformCPU::move(mge::Vector2f pos)
{
	m_transfrom.m_mat[0][3] += pos.x;
	m_transfrom.m_mat[1][3] += pos.y;
	updated = false;
}
void mge::TransformCPU::setAngle(float radians)
{
	float sin, cos;
	//sin = sinf(radians);
	//cos = cosf(radians);
	mge::SinCosf(radians, &sin, &cos);
	m_transfrom.m_mat[0][0] = cos;
	m_transfrom.m_mat[1][0] = -sin;
	m_transfrom.m_mat[0][1] = sin;
	m_transfrom.m_mat[1][1] = cos;
	updated = false;
}
