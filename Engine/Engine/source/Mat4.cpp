#include "EngineBase.h"
#include "D3DXMathEx.h"
#include "Mat4.h"

Mat4::Mat4(const FLOAT* pf) : Base(pf)
{
}

Mat4::Mat4(const D3DMATRIX& m) : Base(m)
{
}

Mat4::Mat4(const Mat4& m) : Base(m)
{
}

Mat4::Mat4(const D3DXFLOAT16* pf) : Base(pf)
{
}

Mat4::Mat4(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14, FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24, FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34, FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44) :
	Base(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44)
{
}

FLOAT& Mat4::operator()(UINT Row, UINT Col)
{
	return Base::operator()(Row, Col);
}

FLOAT Mat4::operator()(UINT Row, UINT Col) const
{
	return Base::operator()(Row, Col);
}

Mat4::operator FLOAT* ()
{
	return Base::operator FLOAT * ();
}

Mat4::operator const FLOAT* () const
{
	return Base::operator FLOAT const * ();
}

Mat4& Mat4::operator*=(const Mat4& m)
{
	*this = Base::operator*=(m);
	return *this;
}

Mat4& Mat4::operator+=(const Mat4& m)
{
	*this = Base::operator+=(m);
	return *this;
}

Mat4& Mat4::operator-=(const Mat4& m)
{
	*this = Base::operator-=(m);
	return *this;
}

Mat4& Mat4::operator*=(FLOAT s)
{
	*this = Base::operator*=(s);
	return *this;
}

Mat4& Mat4::operator/=(FLOAT s)
{
	*this = Base::operator/=(s);
	return *this;
}

Mat4 Mat4::operator+() const
{
	return Base::operator+();
}

Mat4 Mat4::operator-() const
{
	return Base::operator-();
}

Mat4 Mat4::operator*(const Mat4& m) const
{
	return Base::operator*(m);
}

Mat4 Mat4::operator+(const Mat4& m) const
{
	return Base::operator+(m);
}

Mat4 Mat4::operator-(const Mat4& m) const
{
	return Base::operator-(m);
}

Mat4 Mat4::operator*(FLOAT s) const
{
	return Base::operator*(s);
}

Mat4 Mat4::operator/(FLOAT s) const
{
	return Base::operator/(s);
}

Mat4 operator * (FLOAT s, CONST Mat4& m)
{
	return m * s;
}

BOOL Mat4::operator==(const Mat4& m) const
{
	return Base::operator==(m);
}

BOOL Mat4::operator!=(const Mat4& m) const
{
	return Base::operator!=(m);
}

Mat4::operator D3DXMATRIX() const
{
	return *this;
}

void Mat4::Transpose()
{
	D3DXMatrixTranspose(this, this);
}

void Mat4::Inverse()
{
	D3DXMatrixInverse(this, 0, this);
}
Mat4 Mat4::transposed() const
{
	Mat4 m = *this;
	m.Transpose();
	return m;
}

Mat4 Mat4::inversed() const
{
	Mat4 m = *this;
	m.Inverse();
	return m;
}

float Mat4::Determinant() const
{
	return D3DXMatrixDeterminant(this);
}

D3DXVECTOR4 Mat4::GetColumn(const size_t& index) const
{
	return D3DXVECTOR4(m[0][index], m[1][index], m[2][index], m[3][index]);
}

D3DXVECTOR4 Mat4::GetRow(const size_t& index) const
{
	return D3DXVECTOR4(m[index][0], m[index][1], m[index][2], m[index][3]);
}

D3DXVECTOR3 Mat4::MultiplyPoint(const D3DXVECTOR3& p) const
{
	D3DXVECTOR3 V;
	D3DXVec3TransformCoord(&V, &p, this);
	return V;
}

D3DXVECTOR3 Mat4::MultiplyVector(const D3DXVECTOR3& v) const
{
	D3DXVECTOR3 V;
	D3DXVec3TransformNormal(&V, &v, this);
	return V;
}

Mat4 Mat4::one()
{
	return Mat4(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
}

Mat4 Mat4::zero()
{
	return Mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

Mat4 Mat4::Identity()
{
	return Mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

Mat4 Mat4::Translate(const D3DXVECTOR3& t)
{
	Mat4 m;
	D3DXMatrixTranslation(&m, t.x, t.y, t.z);
	return m;
}

Mat4 Mat4::Rotate(const D3DXVECTOR3& r)
{
	//// Pitch, Yaw, Roll
	//Mat4 x, y, z;
	//D3DXMatrixRotationX(&x, r.x);
	//D3DXMatrixRotationY(&y, r.y);
	//D3DXMatrixRotationZ(&z, r.z);
	//// Yaw
	//// Pitch
	//// Roll
	//return y * x * z;

	Mat4 rotate;
	D3DXMatrixRotationYawPitchRoll(&rotate, r.y, r.x, r.z);
	return rotate;
}

Mat4 Mat4::Scale(const D3DXVECTOR3& s)
{
	Mat4 m;
	D3DXMatrixScaling(&m, s.x, s.y, s.z);
	return m;
}

Mat4 Mat4::SRT(const D3DXVECTOR3& s, const D3DXVECTOR3& r, const D3DXVECTOR3& t)
{
	//Mat4 rotate = Rotate(r);

	//Vec3 right = Vec3::right() * s.x * rotate;
	//Vec3 up = Vec3::up() * s.y * rotate;
	//Vec3 forward = Vec3::forawrd() * s.z * rotate;

	//Mat4 m = Mat4(
	//	right.x,	right.y,	right.z,	0,
	//	up.x,		up.y,		up.z,		0,
	//	forward.x,	forward.y,	forward.z,	0,
	//	t.x,		t.y,		t.z,		1
	//	);

	//return m;

	return Scale(s) * Rotate(r) * Translate(t);
}

Mat4 Mat4::TRS(const D3DXVECTOR3& t, const D3DXVECTOR3& r, const D3DXVECTOR3& s)
{
	return Translate(t) * Rotate(r) * Scale(s);
}

D3DXVECTOR4 operator*(const D3DXVECTOR4& v, const Mat4& m)
{
	const D3DXVECTOR4& c1 = m.GetColumn(0);
	const D3DXVECTOR4& c2 = m.GetColumn(1);
	const D3DXVECTOR4& c3 = m.GetColumn(2);
	const D3DXVECTOR4& c4 = m.GetColumn(3);
	const FLOAT& x = D3DXVec4Dot(&c1, &v);
	const FLOAT& y = D3DXVec4Dot(&c2, &v);
	const FLOAT& z = D3DXVec4Dot(&c3, &v);
	const FLOAT& w = D3DXVec4Dot(&c4, &v);
	return D3DXVECTOR4(x, y, z, w);
}

D3DXVECTOR4 operator*(const Mat4& m, const D3DXVECTOR4& v)
{
	const D3DXVECTOR4& r1 = m.GetRow(0);
	const D3DXVECTOR4& r2 = m.GetRow(1);
	const D3DXVECTOR4& r3 = m.GetRow(2);
	const D3DXVECTOR4& r4 = m.GetRow(3);
	const FLOAT& x = D3DXVec4Dot(&r1, &v);
	const FLOAT& y = D3DXVec4Dot(&r2, &v);
	const FLOAT& z = D3DXVec4Dot(&r3, &v);
	const FLOAT& w = D3DXVec4Dot(&r4, &v);
	return D3DXVECTOR4(x, y, z, w);
}