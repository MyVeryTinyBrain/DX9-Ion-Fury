#pragma once

class Mat4;

class Mat3
{
public:
    union
    {
        struct
        {
            float        _11, _12, _13;
            float        _21, _22, _23;
            float        _31, _32, _33;
        };
        struct
        {
            float m[3][3];
        };
        struct
        {
            float a[9];
        };
    };

public:
    Mat3();
    Mat3(CONST FLOAT* pf);
    Mat3(CONST Mat3& M);
    Mat3(CONST D3DXFLOAT16* pf);
    Mat3(
        FLOAT _11, FLOAT _12, FLOAT _13,
        FLOAT _21, FLOAT _22, FLOAT _23,
        FLOAT _31, FLOAT _32, FLOAT _33
    );

public:
    FLOAT& operator () (UINT Row, UINT Col);
    FLOAT  operator () (UINT Row, UINT Col) const;

    operator FLOAT* ();
    operator CONST FLOAT* () const;

    Mat3& operator *= (CONST Mat3& M);
    Mat3& operator += (CONST Mat3& M);
    Mat3& operator -= (CONST Mat3& M);
    Mat3& operator *= (FLOAT s);
    Mat3& operator /= (FLOAT s);

    Mat3 operator + () const; // +m
    Mat3 operator - () const; // -m

    Mat3 operator * (CONST Mat3& M) const;
    Mat3 operator + (CONST Mat3& M) const;
    Mat3 operator - (CONST Mat3& M) const;
    Mat3 operator * (FLOAT s) const;
    Mat3 operator / (FLOAT s) const;

    friend Mat3 operator * (FLOAT s, CONST Mat3& M);

    BOOL operator == (CONST Mat3& M) const;
    BOOL operator != (CONST Mat3& M) const;

public:
    friend D3DXVECTOR3 operator * (const D3DXVECTOR3& v, const Mat3& m); // with column vector
    friend D3DXVECTOR3 operator * (const Mat3& m, const D3DXVECTOR3& v); // with row vector

public:
    void Transpose();
    void Inverse();
    Mat3 transposed() const;
    Mat3 inversed() const;
    float Determinant() const;
    D3DXVECTOR3 GetColumn(const size_t& index) const;
    D3DXVECTOR3 GetRow(const size_t& index) const;
    D3DXVECTOR2 MultiplyPoint(const D3DXVECTOR2& p) const; // with row vector
    D3DXVECTOR2 MultiplyVector(const D3DXVECTOR2& v) const; // with row vector
    Mat4 ToMatrix4() const;

public:
    static Mat3 one();
    static Mat3 zero();
    static Mat3 Identity();
    static Mat3 Translate(const D3DXVECTOR2& t);
    static Mat3 Rotate(const float& r); // r = Roll
    static Mat3 Scale(const D3DXVECTOR2& s);
    static Mat3 SRT(const D3DXVECTOR2& s, const float& r, const D3DXVECTOR2& t);
    static Mat3 TRS(const D3DXVECTOR2& t, const float& r, const D3DXVECTOR2& s);
};

