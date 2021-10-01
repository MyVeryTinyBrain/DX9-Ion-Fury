#pragma once

class Mat4 : public D3DXMATRIX
{
private:
    using Base = D3DXMATRIX;

public:
    Mat4() {};
    Mat4(CONST FLOAT* pf);
    Mat4(CONST D3DMATRIX& m);
    Mat4(CONST Mat4& m);
    Mat4(CONST D3DXFLOAT16* pf);
    Mat4(
        FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
        FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
        FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
        FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44
    );

public:
    FLOAT& operator () (UINT Row, UINT Col);
    FLOAT  operator () (UINT Row, UINT Col) const;

    operator FLOAT* ();
    operator CONST FLOAT* () const;

    Mat4& operator *= (CONST Mat4& m);
    Mat4& operator += (CONST Mat4& m);
    Mat4& operator -= (CONST Mat4& m);
    Mat4& operator *= (FLOAT s);
    Mat4& operator /= (FLOAT s);

    Mat4 operator + () const; // +m
    Mat4 operator - () const; // -m

    Mat4 operator * (CONST Mat4& m) const;
    Mat4 operator + (CONST Mat4& m) const;
    Mat4 operator - (CONST Mat4& m) const;
    Mat4 operator * (FLOAT s) const;
    Mat4 operator / (FLOAT s) const;

    friend Mat4 operator * (FLOAT s, CONST Mat4& m);

    BOOL operator == (CONST Mat4& m) const;
    BOOL operator != (CONST Mat4& m) const;

public:
    operator D3DXMATRIX() const;

    friend D3DXVECTOR4 operator * (const D3DXVECTOR4& v, const Mat4& m); // with column vector
    friend D3DXVECTOR4 operator * (const Mat4& m, const D3DXVECTOR4& v); // with row vector

public:
    void Transpose();
    void Inverse();
    Mat4 transposed() const;
    Mat4 inversed() const;
    float Determinant() const;
    D3DXVECTOR4 GetColumn(const size_t& index) const;
    D3DXVECTOR4 GetRow(const size_t& index) const;
    D3DXVECTOR3 MultiplyPoint(const D3DXVECTOR3& p) const; // with row vector
    D3DXVECTOR3 MultiplyVector(const D3DXVECTOR3& v) const; // with row vector

public:
    static Mat4 one();
    static Mat4 zero();
    static Mat4 Identity();
    static Mat4 Translate(const D3DXVECTOR3& t);
    static Mat4 Rotate(const D3DXVECTOR3& r); // z = Roll, x = Pitch, y = Yaw
    static Mat4 Scale(const D3DXVECTOR3& s);
    static Mat4 SRT(const D3DXVECTOR3& s, const D3DXVECTOR3& r, const D3DXVECTOR3& t);
    static Mat4 TRS(const D3DXVECTOR3& t, const D3DXVECTOR3& r, const D3DXVECTOR3& s);
};
