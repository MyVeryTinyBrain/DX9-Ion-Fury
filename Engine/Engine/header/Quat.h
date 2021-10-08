#pragma once

// Column vector based Quaternion

struct Quat : public D3DXQUATERNION
{
private:
	using Base = D3DXQUATERNION;

public:
	Quat() { x = y = z = w = 0; }
	Quat(CONST FLOAT* pf);
	Quat(CONST D3DXFLOAT16* pf);
	Quat(CONST D3DXQUATERNION& q);
	Quat(CONST Quat& q);
	Quat(FLOAT x, FLOAT y, FLOAT z, FLOAT w);

	operator FLOAT* ();
	operator CONST FLOAT* () const;

	Quat& operator += (CONST Quat& q);
	Quat& operator -= (CONST Quat& q);
	Quat& operator *= (CONST Quat& q);
	Quat& operator *= (FLOAT s);
	Quat& operator /= (FLOAT s);

	Quat  operator + () const;
	Quat  operator - () const;

	Quat operator + (CONST Quat& q) const;
	Quat operator - (CONST Quat& q) const;
	Quat operator * (CONST Quat& q) const;
	Quat operator * (FLOAT s) const;
	Quat operator / (FLOAT s) const;

	friend Quat operator * (FLOAT s, CONST Quat& q);

	BOOL operator == (CONST Quat& q) const;
	BOOL operator != (CONST Quat& q) const;

public:
	friend D3DXVECTOR3 operator * (const Quat& q, const D3DXVECTOR3& v);
	operator D3DXQUATERNION() const;

	D3DXVECTOR3 GetAxis() const;
	D3DXVECTOR3 ToEuler() const;

public:
	float sqrMagnitude() const;
	float magnitude() const;
	Quat normalized() const;
	void Normalize();
	Quat inversed() const;
	void Inverse();
	Mat4 ToMatrixRH() const;
	Mat4 ToMatrixLH() const;
	void SetLookRotation(const Vec3& forward, const Vec3& up);

public:
	static float Dot(const Quat& a, const Quat& b);
	static float Radian(const Quat& a, const Quat& b);
	static float Angle(const Quat& a, const Quat& b);

public:
	static Quat one();
	static Quat zero();
	static Quat Identity();
	static Quat AxisAngle(D3DXVECTOR3 axis, float angle);
	static Quat FromToRotation(const D3DXVECTOR3& from, const D3DXVECTOR3& to);
	static Quat SLerp(const Quat& a, const Quat& b, const float& t);
	static Quat RotateTowards(const Quat& from, const Quat& to, float maxDegreeDelta);
	static Quat LookRotation(Vec3 forward, Vec3 up);
	static Quat FromEuler(float x, float y, float z);
	static bool FromRotationMatrix(Mat4& rotationMatrix, Quat* pOutQuaternion);
};
