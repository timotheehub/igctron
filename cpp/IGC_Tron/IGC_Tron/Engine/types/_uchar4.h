
#ifndef _UCHAR4
#define _UCHAR4

#include "_uchar.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline uchar4 make_uchar4( uchar s )
{
	return make_uchar4( s, s, s, s );
}

static inline uchar4 make_uchar4( uchar3 s )
{
	return make_uchar4( s.x, s.y, s.z, 0 );
}

static inline uchar4 make_uchar4( uchar3 s, uchar w )
{
	return make_uchar4( s.x, s.y, s.z, w );
}

static inline uchar4 make_uchar4( float4 a )
{
	return make_uchar4( uchar(a.x), uchar(a.y), uchar(a.z), uchar(a.w) );
}

static inline uchar4 min( uchar4 a, uchar4 b )
{
	uchar4 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );
	r.z = min( a.z, b.z );
	r.w = min( a.w, b.w );

	return r;
}

static inline uchar4 max( uchar4 a, uchar4 b )
{
	uchar4 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );
	r.z = max( a.z, b.z );
	r.w = max( a.w, b.w );

	return r;
}

static inline uchar4 operator-( uchar4 a )
{
	return make_uchar4( -a.x, -a.y, -a.z, -a.w );
}

static inline uchar4 operator+( uchar4 a, uchar4 b )
{
	return make_uchar4( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w );
}

static inline void operator+=( uchar4& a, uchar4 b )
{
	a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w;
}

static inline uchar4 operator-( uchar4 a, uchar4 b )
{
	return make_uchar4( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w );
}

static inline void operator-=( uchar4& a, uchar4 b )
{
	a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w;
}

static inline uchar4 operator*( uchar4 a, uchar4 b )
{
	return make_uchar4( a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w );
}

static inline uchar4 operator*( uchar4 a, uchar s )
{
	return make_uchar4( a.x * s, a.y * s, a.z * s, a.w * s );
}

static inline uchar4 operator*( uchar s, uchar4 a )
{
	return make_uchar4( a.x * s, a.y * s, a.z * s, a.w * s );
}

static inline void operator*=( uchar4& a, uchar s )
{
	a.x *= s; a.y *= s; a.z *= s; a.w *= s;
}

static inline uchar4 operator/( uchar4 a, uchar4 b )
{
	return make_uchar4( a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w );
}

static inline uchar4 operator/( uchar4 a, uchar s )
{
	return make_uchar4( a.x / s, a.y / s, a.z / s, a.w / s );
}

static inline uchar4 operator/( uchar s, uchar4 a )
{
	return make_uchar4( s / a.x, s / a.y, s / a.z, s / a.w );
}

static inline void operator/=( uchar4& a, uchar s )
{
	a.x /= s; a.y /= s; a.z /= s; a.w /= s;
}

static inline uchar4 clamp( uchar4 v, uchar a, uchar b )
{
	uchar4 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );
	r.z = clamp( v.z, a, b );
	r.w = clamp( v.w, a, b );

	return r;
}

static inline uchar4 clamp( uchar4 v, uchar4 a, uchar4 b )
{
	uchar4 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );
	r.z = clamp( v.z, a.z, b.z );
	r.w = clamp( v.w, a.w, b.w );

	return r;
}

#endif
