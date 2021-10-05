#pragma once

class Color : public D3DXCOLOR
{
public:
    Color() { r = g = b = a = 0; }
    Color(DWORD argb);
    Color(CONST FLOAT* pf);
    Color(CONST D3DXFLOAT16* pf);
    Color(CONST D3DCOLORVALUE& c);
    Color(FLOAT r, FLOAT g, FLOAT b, FLOAT a);
    Color(const D3DXCOLOR& color);
    Color(const Vec4& vec4);

    // casting
    operator DWORD () const;

    operator FLOAT* ();
    operator CONST FLOAT* () const;

    operator D3DCOLORVALUE* ();
    operator CONST D3DCOLORVALUE* () const;

    operator D3DCOLORVALUE& ();
    operator CONST D3DCOLORVALUE& () const;

    operator D3DXCOLOR() const;
    operator Vec4() const;

    // assignment operators
    Color& operator += (CONST Color& c);
    Color& operator -= (CONST Color& c);
    Color& operator *= (FLOAT f);
    Color& operator /= (FLOAT f);

    // unary operators
    Color operator + () const;
    Color operator - () const;

    // binary operators
    Color operator + (CONST Color& c) const;
    Color operator - (CONST Color& c) const;
    Color operator * (FLOAT f) const;
    Color operator / (FLOAT f) const;

    friend Color operator * (FLOAT f, CONST Color& c);

    BOOL operator == (CONST Color&) const;
    BOOL operator != (CONST Color&) const;

    Color& operator = (CONST D3DXCOLOR& color);
    Color& operator = (CONST Vec4& vec4);

    static Color Lerp(const Color& a, const Color& b, float t);

	static Color black();
	static Color white();
	static Color red();
	static Color green();
	static Color blue();
};

