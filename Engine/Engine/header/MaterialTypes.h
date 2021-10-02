#pragma once

enum class CullMode
{
	CW = D3DCULL_CW, 
	CCW = D3DCULL_CCW
};

enum class CmpMode
{
	Never = D3DCMP_NEVER,
    Less = D3DCMP_LESS,
    Equal = D3DCMP_EQUAL,
    LessEqual = D3DCMP_LESSEQUAL,
    Greater = D3DCMP_GREATER,
    NotEqual = D3DCMP_NOTEQUAL,
    GreaterEqaul = D3DCMP_GREATEREQUAL,
    Always = D3DCMP_ALWAYS
};

enum class BlendOpMode
{
    Add = D3DBLENDOP_ADD,
    Subtract = D3DBLENDOP_SUBTRACT,
    ReverseSubtract = D3DBLENDOP_REVSUBTRACT,
    Min = D3DBLENDOP_MIN,
    Max = D3DBLENDOP_MAX
};

enum class BlendFactor
{
    Zero = D3DBLEND_ZERO,
    One = D3DBLEND_ONE,
    SrcColor = D3DBLEND_SRCCOLOR,
    SrcAlpha = D3DBLEND_SRCALPHA,
    DstColor = D3DBLEND_DESTCOLOR,
    DstAlpha = D3DBLEND_DESTALPHA,
    OneMinusSrcColor = D3DBLEND_INVSRCCOLOR,
    OneMinusSrcAlpha = D3DBLEND_INVSRCALPHA,
    OneMinusDstColor = D3DBLEND_INVDESTCOLOR,
    OneMinusDstAlpha = D3DBLEND_INVDESTALPHA,
};
