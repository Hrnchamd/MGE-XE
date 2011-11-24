#pragma once
#ifndef _D3D8HEADER_INL_
#define _D3D8HEADER_INL_

#ifdef __cplusplus

//--------------------------
// Color
//--------------------------

D3DXINLINE
RGBVECTOR::RGBVECTOR( DWORD dw )
{
    CONST FLOAT f = 1.0f / 255.0f;
    r = f * (FLOAT) (unsigned char) (dw >> 16);
    g = f * (FLOAT) (unsigned char) (dw >>  8);
    b = f * (FLOAT) (unsigned char) (dw >>  0);
}

D3DXINLINE
RGBVECTOR::RGBVECTOR( CONST FLOAT* pf )
{
#ifdef D3DX_DEBUG
    if(!pf)
        return;
#endif

    r = pf[0];
    g = pf[1];
    b = pf[2];
}

D3DXINLINE
RGBVECTOR::RGBVECTOR( CONST D3DXFLOAT16* pf )
{
#ifdef D3DX_DEBUG
    if(!pf)
        return;
#endif

    D3DXFloat16To32Array(&r, pf, 3);
}

D3DXINLINE
RGBVECTOR::RGBVECTOR( CONST RGBVECTOR* c )
{
    r = c->r;
    g = c->g;
    b = c->b;
}

D3DXINLINE
RGBVECTOR::RGBVECTOR( CONST RGBVECTOR& c )
{
    r = c.r;
    g = c.g;
    b = c.b;
}

D3DXINLINE
RGBVECTOR::RGBVECTOR( CONST D3DCOLORVALUE& c )
{
    r = c.r;
    g = c.g;
    b = c.b;
}

D3DXINLINE
RGBVECTOR::RGBVECTOR( CONST D3DXCOLOR& c )
{
    r = c.r;
    g = c.g;
    b = c.b;
}

D3DXINLINE
RGBVECTOR::RGBVECTOR( FLOAT fr, FLOAT fg, FLOAT fb )
{
    r = fr;
    g = fg;
    b = fb;
}


// casting
D3DXINLINE
RGBVECTOR::operator DWORD () const
{
    DWORD dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (DWORD) (r * 255.0f + 0.5f);
    DWORD dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (DWORD) (g * 255.0f + 0.5f);
    DWORD dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (DWORD) (b * 255.0f + 0.5f);

    return 0xff000000 | (dwR << 16) | (dwG << 8) | dwB;
}


D3DXINLINE
RGBVECTOR::operator FLOAT * ()
{
    return (FLOAT *) &r;
}

D3DXINLINE
RGBVECTOR::operator CONST FLOAT * () const
{
    return (CONST FLOAT *) &r;
}


// assignment operators
D3DXINLINE RGBVECTOR&
RGBVECTOR::operator += ( CONST RGBVECTOR& c )
{
    r += c.r;
    g += c.g;
    b += c.b;
    return *this;
}

D3DXINLINE RGBVECTOR&
RGBVECTOR::operator -= ( CONST RGBVECTOR& c )
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    return *this;
}

D3DXINLINE RGBVECTOR&
RGBVECTOR::operator += ( CONST D3DXCOLOR& c )
{
    r += c.r;
    g += c.g;
    b += c.b;
    return *this;
}

D3DXINLINE RGBVECTOR&
RGBVECTOR::operator -= ( CONST D3DXCOLOR& c )
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    return *this;
}

D3DXINLINE RGBVECTOR&
RGBVECTOR::operator *= ( FLOAT f )
{
    r *= f;
    g *= f;
    b *= f;
    return *this;
}

D3DXINLINE RGBVECTOR&
RGBVECTOR::operator /= ( FLOAT f )
{
    FLOAT fInv = 1.0f / f;
    r *= fInv;
    g *= fInv;
    b *= fInv;
    return *this;
}


// unary operators
D3DXINLINE RGBVECTOR
RGBVECTOR::operator + () const
{
    return *this;
}

D3DXINLINE RGBVECTOR
RGBVECTOR::operator - () const
{
    return RGBVECTOR(-r, -g, -b);
}


// binary operators
D3DXINLINE RGBVECTOR
RGBVECTOR::operator + ( CONST RGBVECTOR& c ) const
{
    return RGBVECTOR(r + c.r, g + c.g, b + c.b);
}

D3DXINLINE RGBVECTOR
RGBVECTOR::operator - ( CONST RGBVECTOR& c ) const
{
    return RGBVECTOR(r - c.r, g - c.g, b - c.b);
}

D3DXINLINE RGBVECTOR
RGBVECTOR::operator + ( CONST D3DXCOLOR& c ) const
{
    return RGBVECTOR(r + c.r, g + c.g, b + c.b);
}

D3DXINLINE RGBVECTOR
RGBVECTOR::operator - ( CONST D3DXCOLOR& c ) const
{
    return RGBVECTOR(r - c.r, g - c.g, b - c.b);
}

D3DXINLINE RGBVECTOR
RGBVECTOR::operator * ( FLOAT f ) const
{
    return RGBVECTOR(r * f, g * f, b * f);
}

D3DXINLINE RGBVECTOR
RGBVECTOR::operator / ( FLOAT f ) const
{
    FLOAT fInv = 1.0f / f;
    return RGBVECTOR(r * fInv, g * fInv, b * fInv);
}


D3DXINLINE RGBVECTOR
operator * (FLOAT f, CONST RGBVECTOR& c )
{
    return RGBVECTOR(f * c.r, f * c.g, f * c.b);
}


D3DXINLINE BOOL
RGBVECTOR::operator == ( CONST RGBVECTOR& c ) const
{
    return r == c.r && g == c.g && b == c.b;
}

D3DXINLINE BOOL
RGBVECTOR::operator != ( CONST RGBVECTOR& c ) const
{
    return r != c.r || g != c.g || b != c.b;
}

D3DXINLINE BOOL
RGBVECTOR::operator == ( CONST D3DXCOLOR& c ) const
{
    return r == c.r && g == c.g && b == c.b && c.a == 1;
}

D3DXINLINE BOOL
RGBVECTOR::operator != ( CONST D3DXCOLOR& c ) const
{
    return r != c.r || g != c.g || b != c.b || c.a != 1;
}


#endif /* __cplusplus */

#endif /* _D3D8HEADER_INL_ */
