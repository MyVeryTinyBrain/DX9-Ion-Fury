#include "EngineBase.h"
#include "D3DXMathEx.h"
#include "Quat.h"

using namespace MathEx;

Quat::Quat(CONST FLOAT* pf) : Base(pf)
{
}

Quat::Quat(CONST D3DXFLOAT16* pf) : Base(pf)
{
}

Quat::Quat(CONST D3DXQUATERNION& q) : Base(q)
{
}

Quat::Quat(CONST Quat& q) : Base(q)
{
}

Quat::Quat(FLOAT x, FLOAT y, FLOAT z, FLOAT w) : Base(x, y, z, w)
{
}

Quat::operator FLOAT* ()
{
	return Base::operator FLOAT * ();
}

Quat::operator CONST FLOAT* () const
{
	return Base::operator const FLOAT * ();
}

Quat& Quat::operator+=(CONST Quat& q)
{
	D3DXQUATERNION Q = Base::operator+=(q);
	x = Q.x;
	y = Q.y;
	z = Q.z;
	w = Q.w;
	return *this;
}

Quat& Quat::operator-=(CONST Quat& q)
{
	D3DXQUATERNION Q = Base::operator-=(q);
	x = Q.x;
	y = Q.y;
	z = Q.z;
	w = Q.w;
	return *this;
}

Quat& Quat::operator*=(CONST Quat& q)
{
	const Quat& thisQ = *this;
	*this = thisQ * q;
	return *this;
}

Quat& Quat::operator*=(FLOAT s)
{
	D3DXQUATERNION Q = Base::operator*=(s);
	x = Q.x;
	y = Q.y;
	z = Q.z;
	w = Q.w;
	return *this;
}

Quat& Quat::operator/=(FLOAT s)
{
	D3DXQUATERNION Q = Base::operator/=(s);
	x = Q.x;
	y = Q.y;
	z = Q.z;
	w = Q.w;
	return *this;
}

Quat Quat::operator+() const
{
	return (Quat)Base::operator+();
}

Quat Quat::operator-() const
{
	return (Quat)Base::operator-();
}

Quat Quat::operator+(CONST Quat& q) const
{
	return (Quat)Base::operator+(q);
}

Quat Quat::operator-(CONST Quat& q) const
{
	return (Quat)Base::operator-(q);
}

Quat Quat::operator*(CONST Quat& q) const
{
	//return (Quat)Base::operator*(q);

	const Quat& lhs = *this;
	const Quat& rhs = q;
	return Quat(
		lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y, 
		lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z, 
		lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x, 
		lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z);
}

Quat Quat::operator*(FLOAT s) const
{
	return (Quat)Base::operator*(s);
}

Quat Quat::operator/(FLOAT s) const
{
	return (Quat)Base::operator/(s);
}

BOOL Quat::operator==(CONST Quat& q) const
{
	return Base::operator==(q);
}

BOOL Quat::operator!=(CONST Quat& q) const
{
	return Base::operator!=(q);
}

Quat::operator D3DXQUATERNION() const
{
	return *this;
}

D3DXVECTOR3 Quat::GetAxis() const
{
	D3DXVECTOR3 axis(x, y, z);
	D3DXVec3Normalize(&axis, &axis);
	return axis;
}

D3DXVECTOR3 Quat::ToEuler() const
{
	const Quat& q = *this;
	Vec3 euler;

	// if the input quaternion is normalized, this is exactly one. Otherwise, this acts as a correction factor for the quaternion's not-normalizedness
	float unit = (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w);

	// this will have a magnitude of 0.5 or greater if and only if this is a singularity case
	float test = q.x * q.w - q.y * q.z;

	if (test > 0.49999f * unit) // singularity at north pole
	{
		euler.x = PI / 2;
		euler.y = 2.0f * atan2f(q.y, q.x);
		euler.z = 0;
	}
	else if (test < -0.49999f * unit) // singularity at south pole
	{
		euler.x = -PI / 2;
		euler.y = -2.0f * atan2f(q.y, q.x);
		euler.z = 0;
	}
	else // no singularity - this is the majority of cases
	{
		euler.x = asinf(2.0f * (q.w * q.x - q.y * q.z));
		euler.y = atan2f(2.0f * q.w * q.y + 2.0f * q.z * q.x, 1 - 2.0f * (q.x * q.x + q.y * q.y));
		euler.z = atan2f(2.0f * q.w * q.z + 2.0f * q.x * q.y, 1 - 2.0f * (q.z * q.z + q.x * q.x));
	}

	// all the math so far has been done in radians. Before returning, we convert to degrees...
	euler *= Rad2Deg;

	//...and then ensure the degree values are between 0 and 360
	euler.x = fmodf(euler.x, 360.0f);
	euler.y = fmodf(euler.y, 360.0f);
	euler.z = fmodf(euler.z, 360.0f);

	return euler;
}

float Quat::sqrMagnitude() const
{
	return D3DXQuaternionLengthSq(this);
}

float Quat::magnitude() const
{
	return D3DXQuaternionLength(this);
}

Quat Quat::normalized() const
{
	Quat q = *this;
	q.Normalize();
	return q;
}

void Quat::Normalize()
{
	D3DXQuaternionNormalize(this, this);
}

Quat Quat::inversed() const
{
	Quat q = *this;
	q.Inverse();
	return q;
}

void Quat::Inverse()
{
	D3DXQuaternionInverse(this, this);
}

Mat4 Quat::ToMatrixRH() const
{
	return Mat4 (
		1.0f - 2.0f * y * y - 2.0f * z * z, 2.0f * x * y - 2.0f * z * w, 2.0f * x * z + 2.0f * y * w, 0.0f,
		2.0f * x * y + 2.0f * z * w, 1.0f - 2.0f * x * x - 2.0f * z * z, 2.0f * y * z - 2.0f * x * w, 0.0f,
		2.0f * x * z - 2.0f * y * w, 2.0f * y * z + 2.0f * x * w, 1.0f - 2.0f * x * x - 2.0f * y * y, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Mat4 Quat::ToMatrixLH() const
{
	return ToMatrixRH().inversed();
}

void Quat::SetLookRotation(const Vec3& forward, const Vec3& up)
{
	*this = LookRotation(forward, up);
}

float Quat::Dot(const Quat& a, const Quat& b)
{
	return D3DXQuaternionDot(&a, &b);
}

float Quat::Radian(const Quat& a, const Quat& b)
{
	float f = Dot(a, b);
	return acosf(min(fabsf(f), 1.0f)) * 2.0f;
}

float Quat::Angle(const Quat& a, const Quat& b)
{
	return Radian(a, b) * Rad2Deg;
}

Quat Quat::one()
{
	return Quat(1, 1, 1, 1);
}

Quat Quat::zero()
{
	return Quat(0, 0, 0, 0);
}

Quat Quat::Identity()
{
	return Quat(0, 0, 0, 1);
}

Quat Quat::AxisAngle(D3DXVECTOR3 axis, float angle)
{
	Quat q;
	D3DXQuaternionRotationAxis(&q, &axis, angle * Deg2Rad);
	return q;

	//D3DXVec3Normalize(&axis, &axis);
	//float sina = sinf(0.5f * angle * Deg2Rad);
	//float cosa = cosf(0.5f * angle * Deg2Rad);
	//Vec3 v = axis * sina;
	//return Quat(v.x, v.y, v.z, cosa);
}

Quat Quat::FromToRotation(const D3DXVECTOR3& from, const D3DXVECTOR3& to)
{
	// https://answers.unity.com/questions/1668856/whats-the-source-code-of-quaternionfromtorotation.html

	D3DXVECTOR3 axis;
	D3DXVec3Cross(&axis, &from, &to);

	float dot = D3DXVec3Dot(&from, &to);
	float denominator = D3DXVec3Length(&from) * D3DXVec3Length(&to);
	float cos;
	if (denominator == 0)
		cos = 0;
	else
		cos = dot / denominator;
	if (cos < -1.0f) cos = -1.0f;
	else if (cos > +1.0f) cos = +1.0f;
	float rAngle = acosf(cos);
	float angle = rAngle * 180.0f / D3DX_PI;

	if (angle >= 179.9196f)
	{
		D3DXVECTOR3 r;
		D3DXVECTOR3 right(1, 0, 0);
		D3DXVec3Cross(&r, &from, &right);
		D3DXVec3Cross(&axis, &r, &from);

		float axisSqrtMagnitude = axis.x * axis.x + axis.y * axis.y + axis.z * axis.z;

		if (axisSqrtMagnitude < 0.000001f)
			axis = D3DXVECTOR3(0, 0, 1);
	}

	D3DXVec3Normalize(&axis, &axis);
	return AxisAngle(axis, angle);
}

Quat Quat::SLerp(const Quat& a, const Quat& b, const float& t)
{
	Quat q;
	D3DXQuaternionSlerp(&q, &a, &b, t);
	return q;
}

Quat Quat::RotateTowards(const Quat& from, const Quat& to, float maxDegreeDelta)
{
	float angle = Angle(from, to);
	if (angle == 0) return to;
	float t = min(1.0f, maxDegreeDelta / angle);
	return SLerp(from, to, t);
}

Quat Quat::LookRotation(Vec3 forward, Vec3 up)
{
	forward.Normalize();
	Vec3 right = (Vec3::Cross(up, forward)).normalized();
	up = Vec3::Cross(forward, right);
	auto m00 = right.x;
	auto m01 = right.y;
	auto m02 = right.z;
	auto m10 = up.x;
	auto m11 = up.y;
	auto m12 = up.z;
	auto m20 = forward.x;
	auto m21 = forward.y;
	auto m22 = forward.z;


	float num8 = (m00 + m11) + m22;
	Quat quaternion;
	if (num8 > 0.0f)
	{
		auto num = sqrtf(num8 + 1.0f);
		quaternion.w = num * 0.5f;
		num = 0.5f / num;
		quaternion.x = (m12 - m21) * num;
		quaternion.y = (m20 - m02) * num;
		quaternion.z = (m01 - m10) * num;
		return quaternion;
	}
	if ((m00 >= m11) && (m00 >= m22))
	{
		auto num7 = sqrtf(((1.0f + m00) - m11) - m22);
		auto num4 = 0.5f / num7;
		quaternion.x = 0.5f * num7;
		quaternion.y = (m01 + m10) * num4;
		quaternion.z = (m02 + m20) * num4;
		quaternion.w = (m12 - m21) * num4;
		return quaternion;
	}
	if (m11 > m22)
	{
		auto num6 = sqrtf(((1.0f + m11) - m00) - m22);
		auto num3 = 0.5f / num6;
		quaternion.x = (m10 + m01) * num3;
		quaternion.y = 0.5f * num6;
		quaternion.z = (m21 + m12) * num3;
		quaternion.w = (m20 - m02) * num3;
		return quaternion;
	}
	auto num5 = sqrtf(((1.0f + m22) - m00) - m11);
	auto num2 = 0.5f / num5;
	quaternion.x = (m20 + m02) * num2;
	quaternion.y = (m21 + m12) * num2;
	quaternion.z = 0.5f * num5;
	quaternion.w = (m01 - m10) * num2;
	return quaternion;
}

Quat Quat::FromEuler(float x, float y, float z)
{
	float xOver2 = x * Deg2Rad * 0.5f;
	float yOver2 = y * Deg2Rad * 0.5f;
	float zOver2 = z * Deg2Rad * 0.5f;

	float sinXOver2 = sinf(xOver2);
	float cosXOver2 = cosf(xOver2);
	float sinYOver2 = sinf(yOver2);
	float cosYOver2 = cosf(yOver2);
	float sinZOver2 = sinf(zOver2);
	float cosZOver2 = cosf(zOver2);

	Quat result;
	result.x = cosYOver2 * sinXOver2 * cosZOver2 + sinYOver2 * cosXOver2 * sinZOver2;
	result.y = sinYOver2 * cosXOver2 * cosZOver2 - cosYOver2 * sinXOver2 * sinZOver2;
	result.z = cosYOver2 * cosXOver2 * sinZOver2 - sinYOver2 * sinXOver2 * cosZOver2;
	result.w = cosYOver2 * cosXOver2 * cosZOver2 + sinYOver2 * sinXOver2 * sinZOver2;

	return result;

	//Quat q;
	//D3DXQuaternionRotationYawPitchRoll(&q, y * Deg2Rad, x * Deg2Rad, z * Deg2Rad);
	//return q;

	//Quat yaw = Quat::AxisAngle(Vec3::up(), y);
	//Quat pitch = Quat::AxisAngle(Vec3::right(), x);
	//Quat roll = Quat::AxisAngle(Vec3::forawrd(), z);
	//return yaw * pitch * roll;
}

bool Quat::FromRotationMatrix(Mat4& rotationMatrix, Quat* pOutQuaternion)
{
	auto isRotationMatrix = [](const Mat4& matrix)
	{
		// 직교행렬 검사
		Mat4 transposed = matrix.transposed();
		Mat4 shouldBeIdentity = transposed * matrix;
		return fabsf(1.0f - shouldBeIdentity.Determinant()) <= 1e-6;
	};

	auto sign = [](float value)
	{
		if (value > 0) return +1.0f;
		else return -1.0f;
	};

	if (!isRotationMatrix(rotationMatrix)) return false;

	const Mat4& m = rotationMatrix.transposed();

	Quat q;
	q.w = sqrtf(max(0, 1 + m._11 + m._22 + m._33)) / 2;
	q.x = sqrtf(max(0, 1 + m._11 - m._22 - m._33)) / 2;
	q.y = sqrtf(max(0, 1 - m._11 + m._22 - m._33)) / 2;
	q.z = sqrtf(max(0, 1 - m._11 - m._22 + m._33)) / 2;
	q.x *= sign(q.x * (m._32 - m._23));
	q.y *= sign(q.y * (m._13 - m._31));
	q.z *= sign(q.z * (m._21 - m._12));
		
	*pOutQuaternion = q;

	return true;
}

Quat operator*(FLOAT s, CONST Quat& q)
{
	return q * s;
}

D3DXVECTOR3 operator*(const Quat& q, const D3DXVECTOR3& v)
{
	Quat qv = Quat(v.x, v.y, v.z, 0);

	// qInv = 켤레쿼터니언 / 쿼터니언 크기의 제곱
	Quat qInv;
	D3DXQuaternionInverse(&qInv, &q);

	Quat res = q * qv * qInv;
	return D3DXVECTOR3(res.x, res.y, res.z);
}
