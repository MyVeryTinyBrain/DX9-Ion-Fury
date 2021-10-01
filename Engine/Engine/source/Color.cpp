#include "EngineBase.h"
#include "D3DXMathEx.h"
#include "Color.h"

Color::Color(DWORD argb) : D3DXCOLOR(argb)
{
}

Color::Color(const FLOAT* pf) : D3DXCOLOR(pf)
{
}

Color::Color(const D3DXFLOAT16* pf) : D3DXCOLOR(pf)
{
}

Color::Color(const D3DCOLORVALUE& c) : D3DXCOLOR(c)
{
}

Color::Color(FLOAT r, FLOAT g, FLOAT b, FLOAT a) : D3DXCOLOR(r, g, b, a)
{
}

Color::Color(const D3DXCOLOR& color) : D3DXCOLOR(color)
{
}

Color::Color(const Vec4& vec4) : D3DXCOLOR(vec4.x, vec4.y, vec4.z, vec4.w)
{
}

Color::operator DWORD() const
{
	return D3DXCOLOR::operator DWORD();
}

Color::operator FLOAT* ()
{
	return D3DXCOLOR::operator FLOAT * ();
}

Color::operator const FLOAT* () const
{
	return D3DXCOLOR::operator const FLOAT * ();
}

Color::operator D3DCOLORVALUE* ()
{
	return D3DXCOLOR::operator D3DCOLORVALUE * ();
}

Color::operator const D3DCOLORVALUE* () const
{
	return D3DXCOLOR::operator D3DCOLORVALUE const * ();
}

Color::operator D3DCOLORVALUE& ()
{
	return D3DXCOLOR::operator D3DCOLORVALUE & ();
}

Color::operator const D3DCOLORVALUE& () const
{
	return D3DXCOLOR::operator const D3DCOLORVALUE & ();
}

Color::operator D3DXCOLOR() const
{
	return *this;
}

Color::operator Vec4() const
{
	return Vec4(r, g, b, a);
}

Color& Color::operator+=(const Color& c)
{
	((D3DXCOLOR)*this).operator+=(c);
	return *this;
}

Color& Color::operator-=(const Color& c)
{
	((D3DXCOLOR)*this).operator-=(c);
	return *this;
}

Color& Color::operator*=(FLOAT f)
{
	((D3DXCOLOR)*this).operator*=(f);
	return *this;
}

Color& Color::operator/=(FLOAT f)
{
	((D3DXCOLOR)*this).operator/=(f);
	return *this;
}

Color Color::operator+() const
{
	return ((D3DXCOLOR)*this).operator+();
}

Color Color::operator-() const
{
	return ((D3DXCOLOR)*this).operator-();
}

Color Color::operator+(const Color& c) const
{
	return ((D3DXCOLOR)*this).operator+(c);
}

Color Color::operator-(const Color& c) const
{
	return ((D3DXCOLOR)*this).operator-(c);
}

Color Color::operator*(FLOAT f) const
{
	return ((D3DXCOLOR)*this).operator*(f);
}

Color Color::operator/(FLOAT f) const
{
	return ((D3DXCOLOR)*this).operator/(f);
}

BOOL Color::operator==(const Color& c) const
{
	return ((D3DXCOLOR)*this).operator==(c);
}

BOOL Color::operator!=(const Color& c) const
{
	return ((D3DXCOLOR)*this).operator!=(c);
}

Color& Color::operator=(const D3DXCOLOR& color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
	return *this;
}

Color& Color::operator=(const Vec4& vec4)
{
	*this = D3DXCOLOR::operator=(D3DXCOLOR(vec4.x, vec4.y, vec4.z, vec4.w));
	return *this;
}

Color Color::Lerp(const Color& a, const Color& b, float t)
{
	Color res;
	D3DXColorLerp(&res, &a, &b, t);
	return res;
}

Color Color::black()
{
	return Color(0, 0, 0, 1);
}

Color Color::white()
{
	return Color(1, 1, 1, 1);
}

Color Color::red()
{
	return Color(1, 0, 0, 1);
}

Color Color::green()
{
	return Color(0, 1, 0, 1);
}

Color Color::blue()
{
	return Color(0, 0, 1, 1);
}

Color operator*(FLOAT f, const Color& c)
{
	return c * f;
}
