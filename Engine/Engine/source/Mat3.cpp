#include "EngineBase.h"
#include "D3DXMathEx.h"
#include "Mat3.h"

Mat3::Mat3()
{
	ZeroMemory(m, sizeof(float) * 9);
}

Mat3::Mat3(const FLOAT* pf)
{
	memcpy(m, pf, sizeof(float) * 9);
}

Mat3::Mat3(const Mat3& M)
{
	memcpy(m, &M, sizeof(float) * 9);
}

Mat3::Mat3(const D3DXFLOAT16* pf)
{
	D3DXFloat16To32Array(&_11, pf, 9);
}

Mat3::Mat3(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _31, FLOAT _32, FLOAT _33)
{
	this->_11 = _11;
	this->_12 = _12;
	this->_13 = _13;
	this->_21 = _21;
	this->_22 = _22;
	this->_23 = _23;
	this->_31 = _31;
	this->_32 = _32;
	this->_33 = _33;
}

FLOAT& Mat3::operator()(UINT Row, UINT Col)
{
	return m[Row][Col];
}

FLOAT Mat3::operator()(UINT Row, UINT Col) const
{
	return m[Row][Col];
}

Mat3::operator FLOAT* ()
{
	return &_11;
}

Mat3::operator const FLOAT* () const
{
	return &_11;
}

Mat3& Mat3::operator*=(const Mat3& M)
{
	D3DXVECTOR3 r1 = GetRow(0);
	D3DXVECTOR3 r2 = GetRow(1);
	D3DXVECTOR3 r3 = GetRow(2);
	D3DXVECTOR3 c1 = M.GetColumn(0);
	D3DXVECTOR3 c2 = M.GetColumn(1);
	D3DXVECTOR3 c3 = M.GetColumn(2);
	_11 = D3DXVec3Dot(&r1, &c1);
	_12 = D3DXVec3Dot(&r1, &c2);
	_13 = D3DXVec3Dot(&r1, &c3);
	_21 = D3DXVec3Dot(&r2, &c1);
	_22 = D3DXVec3Dot(&r2, &c2);
	_23 = D3DXVec3Dot(&r2, &c3);
	_31 = D3DXVec3Dot(&r3, &c1);
	_32 = D3DXVec3Dot(&r3, &c2);
	_33 = D3DXVec3Dot(&r3, &c3);
	return *this;
}

Mat3& Mat3::operator+=(const Mat3& M)
{
	for (size_t i = 0; i < 9; ++i)
		a[i] += M.a[i];
	return *this;
}

Mat3& Mat3::operator-=(const Mat3& M)
{
	for (size_t i = 0; i < 9; ++i)
		a[i] -= M.a[i];
	return *this;
}

Mat3& Mat3::operator*=(FLOAT s)
{
	for (size_t i = 0; i < 9; ++i)
		a[i] *= s;
	return *this;
}

Mat3& Mat3::operator/=(FLOAT s)
{
	for (size_t i = 0; i < 9; ++i)
		a[i] /= s;
	return *this;
}

Mat3 Mat3::operator+() const
{
	Mat3 M = *this;
	for (size_t i = 0; i < 9; ++i)
		M.a[i] *= 1;
	return M;
}

Mat3 Mat3::operator-() const
{
	Mat3 M = *this;
	for (size_t i = 0; i < 9; ++i)
		M.a[i] *= -1;
	return M;
}

Mat3 Mat3::operator*(const Mat3& M) const
{
	D3DXVECTOR3 r1 = GetRow(0);
	D3DXVECTOR3 r2 = GetRow(1);
	D3DXVECTOR3 r3 = GetRow(2);
	D3DXVECTOR3 c1 = M.GetColumn(0);
	D3DXVECTOR3 c2 = M.GetColumn(1);
	D3DXVECTOR3 c3 = M.GetColumn(2);
	return {
	D3DXVec3Dot(&r1, &c1),
	D3DXVec3Dot(&r1, &c2),
	D3DXVec3Dot(&r1, &c3),
	D3DXVec3Dot(&r2, &c1),
	D3DXVec3Dot(&r2, &c2),
	D3DXVec3Dot(&r2, &c3),
	D3DXVec3Dot(&r3, &c1),
	D3DXVec3Dot(&r3, &c2),
	D3DXVec3Dot(&r3, &c3)
	};
}

Mat3 Mat3::operator+(const Mat3& M) const
{
	Mat3 M2 = *this;
	M2 += M;
	return M2;
}

Mat3 Mat3::operator-(const Mat3& M) const
{
	Mat3 M2 = *this;
	M2 -= M;
	return M2;
}

Mat3 Mat3::operator*(FLOAT s) const
{
	Mat3 M2 = *this;
	M2 *= s;
	return M2;
}

Mat3 Mat3::operator/(FLOAT s) const
{
	Mat3 M2 = *this;
	M2 /= s;
	return M2;
}

BOOL Mat3::operator==(const Mat3& m) const
{
	for (size_t i = 0; i < 9; ++i)
		if (a[i] != m.a[i])
			return false;
	return true;
}

BOOL Mat3::operator!=(const Mat3& m) const
{
	return !(*this == m);
}

void Mat3::Transpose()
{
	Mat3 M = *this;
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			m[i][j] = M.m[j][i];
}

void Mat3::Inverse()
{
	float D = Determinant();
	Transpose();
	float d11 = _22 * _33 - _23 * _32;
	float d12 = _21 * _33 - _23 * _31;
	float d13 = _21 * _32 - _22 * _31;
	float d21 = _12 * _33 - _13 * _32;
	float d22 = _11 * _33 - _13 * _31;
	float d23 = _11 * _32 - _12 * _31;
	float d31 = _12 * _23 - _13 * _22;
	float d32 = _11 * _23 - _13 * _21;
	float d33 = _11 * _22 - _12 * _21;
	_11 = +d11;
	_12 = -d12;
	_13 = +d13;
	_21 = -d21;
	_22 = +d22;
	_23 = -d23;
	_31 = +d31;
	_32 = -d32;
	_33 = +d33;
	*this /= D;
}

Mat3 Mat3::transposed() const
{
	Mat3 m = *this;
	m.Transpose();
	return m;
}

Mat3 Mat3::inversed() const
{
	Mat3 M = *this;
	M.Inverse();
	return M;
}

float Mat3::Determinant() const
{
	const float& a = _11;
	const float& b = _12;
	const float& c = _13;
	const float& d = _21;
	const float& e = _22;
	const float& f = _23;
	const float& g = _31;
	const float& h = _32;
	const float& i = _33;
	return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
		
}

D3DXVECTOR3 Mat3::GetColumn(const size_t& index) const
{
	return D3DXVECTOR3(m[0][index], m[1][index], m[2][index]);
}

D3DXVECTOR3 Mat3::GetRow(const size_t& index) const
{
	return D3DXVECTOR3(m[index][0], m[index][1], m[index][2]);
}

D3DXVECTOR2 Mat3::MultiplyPoint(const D3DXVECTOR2& p) const
{
	D3DXVECTOR3 V = { p.x,p.y,1 };
	const D3DXVECTOR3& c1 = GetColumn(0);
	const D3DXVECTOR3& c2 = GetColumn(1);
	const D3DXVECTOR3& c3 = GetColumn(2);
	const FLOAT& x = D3DXVec3Dot(&c1, &V);
	const FLOAT& y = D3DXVec3Dot(&c2, &V);
	const FLOAT& z = D3DXVec3Dot(&c3, &V);
	return D3DXVECTOR2(V.x, V.y);
}

D3DXVECTOR2 Mat3::MultiplyVector(const D3DXVECTOR2& v) const
{
	D3DXVECTOR3 V = { v.x,v.y,0 };
	const D3DXVECTOR3& c1 = GetColumn(0);
	const D3DXVECTOR3& c2 = GetColumn(1);
	const D3DXVECTOR3& c3 = GetColumn(2);
	const FLOAT& x = D3DXVec3Dot(&c1, &V);
	const FLOAT& y = D3DXVec3Dot(&c2, &V);
	const FLOAT& z = D3DXVec3Dot(&c3, &V);
	return D3DXVECTOR2(V.x, V.y);
}

Mat4 Mat3::ToMatrix4() const
{
	return Mat4(
		_11,	_12,	_13,	0,
		_21,	_22,	_23,	0,
		_31,	_32,	_33,	0,
		0,		0,		0,		1
	);
}

Mat3 Mat3::one()
{
	return Mat3(1, 1, 1, 1, 1, 1, 1, 1, 1);
}

Mat3 Mat3::zero()
{
	return Mat3(0, 0, 0, 0, 0, 0, 0, 0, 0);
}

Mat3 Mat3::Identity()
{
	return Mat3(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	);
}

Mat3 Mat3::Translate(const D3DXVECTOR2& t)
{
	return Mat3(
		1,		0,		0,
		0,		1,		0,
		t.x,	t.y,	1
	);
}

Mat3 Mat3::Rotate(const float& r)
{
	float cos = cosf(r);
	float sin = sinf(r);
	return Mat3(
		cos,	sin,	0,
		-sin,	cos,	0,
		0,		0,		1
	);
}

Mat3 Mat3::Scale(const D3DXVECTOR2& s)
{
	return Mat3(
		s.x,	0,		0,
		0,		s.y,	0,
		0,		0,		1
	);
}

Mat3 Mat3::SRT(const D3DXVECTOR2& s, const float& r, const D3DXVECTOR2& t)
{
	return Scale(s) * Rotate(r) * Translate(t);
}

Mat3 Mat3::TRS(const D3DXVECTOR2& t, const float& r, const D3DXVECTOR2& s)
{
	return Translate(t) * Rotate(r) * Scale(s);
}

Mat3 operator*(FLOAT s, const Mat3& m)
{
	return m * s;
}

D3DXVECTOR3 operator*(const D3DXVECTOR3& v, const Mat3& m)
{
	const D3DXVECTOR3& c1 = m.GetColumn(0);
	const D3DXVECTOR3& c2 = m.GetColumn(1);
	const D3DXVECTOR3& c3 = m.GetColumn(2);
	const FLOAT& x = D3DXVec3Dot(&c1, &v);
	const FLOAT& y = D3DXVec3Dot(&c2, &v);
	const FLOAT& z = D3DXVec3Dot(&c3, &v);
	return D3DXVECTOR3{ x,y,z };
}

D3DXVECTOR3 operator*(const Mat3& m, const D3DXVECTOR3& v)
{
	const D3DXVECTOR3& r1 = m.GetRow(0);
	const D3DXVECTOR3& r2 = m.GetRow(1);
	const D3DXVECTOR3& r3 = m.GetRow(2);
	const FLOAT& x = D3DXVec3Dot(&r1, &v);
	const FLOAT& y = D3DXVec3Dot(&r2, &v);
	const FLOAT& z = D3DXVec3Dot(&r3, &v);
	return D3DXVECTOR3(x, y, z);
}
