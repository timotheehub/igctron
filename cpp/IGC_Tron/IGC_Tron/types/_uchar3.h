
#ifndef _UCHAR3
#define _UCHAR3

#include "_uchar.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline uchar3 make_uchar3( uchar s )
{
	return make_uchar3( s, s, s );
}

static inline uchar3 make_uchar3( uchar2 s )
{
	return make_uchar3( s.x, s.y, 0 );
}

static inline uchar3 make_uchar3( uchar2 s, uchar w )
{
	return make_uchar3( s.x, s.y, w );
}

static inline uchar3 make_uchar3( float3 a )
{
	return make_uchar3( uchar(a.x), uchar(a.y), uchar(a.z) );
}

static inline uchar3 min( uchar3 a, uchar3 b )
{
	uchar3 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );
	r.z = min( a.z, b.z );

	return r;
}

static inline uchar3 max( uchar3 a, uchar3 b )
{
	uchar3 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );
	r.z = max( a.z, b.z );

	return r;
}

static inline uchar3 operator-( uchar3 a )
{
	return make_uchar3( -a.x, -a.y, -a.z );
}

static inline uchar3 operator+( uchar3 a, uchar3 b )
{
	return make_uchar3( a.x + b.x, a.y + b.y, a.z + b.z );
}

static inline void operator+=( uchar3& a, uchar3 b )
{
	a.x += b.x; a.y += b.y; a.z += b.z;
}

static inline uchar3 operator-( uchar3 a, uchar3 b )
{
	return make_uchar3( a.x - b.x, a.y - b.y, a.z - b.z );
}

static inline void operator-=( uchar3& a, uchar3 b )
{
	a.x -= b.x; a.y -= b.y; a.z -= b.z;
}

static inline uchar3 operator*( uchar3 a, uchar3 b )
{
	return make_uchar3( a.x * b.x, a.y * b.y, a.z * b.z );
}

static inline uchar3 operator*( uchar3 a, uchar s )
{
	return make_uchar3( a.x * s, a.y * s, a.z * s );
}

static inline uchar3 operator*( uchar s, uchar3 a )
{
	return make_uchar3( a.x * s, a.y * s, a.z * s );
}

static inline void operator*=( uchar3& a, uchar s )
{
	a.x *= s; a.y *= s; a.z *= s;
}

static inline uchar3 operator/( uchar3 a, uchar3 b )
{
	return make_uchar3( a.x / b.x, a.y / b.y, a.z / b.z );
}

static inline uchar3 operator/( uchar3 a, uchar s )
{
	return make_uchar3( a.x / s, a.y / s, a.z / s );
}

static inline uchar3 operator/( uchar s, uchar3 a )
{
	return make_uchar3( s / a.x, s / a.y, s / a.z );
}

static inline void operator/=( uchar3& a, uchar s )
{
	a.x /= s; a.y /= s; a.z /= s;
}

static inline uchar3 clamp( uchar3 v, uchar a, uchar b )
{
	uchar3 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );
	r.z = clamp( v.z, a, b );

	return r;
}

static inline uchar3 clamp( uchar3 v, uchar3 a, uchar3 b )
{
	uchar3 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );
	r.z = clamp( v.z, a.z, b.z );

	return r;
}

#endif
