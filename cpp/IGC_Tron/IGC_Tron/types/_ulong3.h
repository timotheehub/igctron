
#ifndef _ULONG3
#define _ULONG3

#include "_ulong.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline ulong3 make_ulong3( ulong s )
{
	return make_ulong3( s, s, s );
}

static inline ulong3 make_ulong3( ulong2 s )
{
	return make_ulong3( s.x, s.y, 0 );
}

static inline ulong3 make_ulong3( ulong2 s, ulong w )
{
	return make_ulong3( s.x, s.y, w );
}

static inline ulong3 make_ulong3( float3 a )
{
	return make_ulong3( ulong(a.x), ulong(a.y), ulong(a.z) );
}

static inline ulong3 min( ulong3 a, ulong3 b )
{
	ulong3 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );
	r.z = min( a.z, b.z );

	return r;
}

static inline ulong3 max( ulong3 a, ulong3 b )
{
	ulong3 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );
	r.z = max( a.z, b.z );

	return r;
}

static inline ulong3 operator+( ulong3 a, ulong3 b )
{
	return make_ulong3( a.x + b.x, a.y + b.y, a.z + b.z );
}

static inline void operator+=( ulong3& a, ulong3 b )
{
	a.x += b.x; a.y += b.y; a.z += b.z;
}

static inline ulong3 operator-( ulong3 a, ulong3 b )
{
	return make_ulong3( a.x - b.x, a.y - b.y, a.z - b.z );
}

static inline void operator-=( ulong3& a, ulong3 b )
{
	a.x -= b.x; a.y -= b.y; a.z -= b.z;
}

static inline ulong3 operator*( ulong3 a, ulong3 b )
{
	return make_ulong3( a.x * b.x, a.y * b.y, a.z * b.z );
}

static inline ulong3 operator*( ulong3 a, ulong s )
{
	return make_ulong3( a.x * s, a.y * s, a.z * s );
}

static inline ulong3 operator*( ulong s, ulong3 a )
{
	return make_ulong3( a.x * s, a.y * s, a.z * s );
}

static inline void operator*=( ulong3& a, ulong s )
{
	a.x *= s; a.y *= s; a.z *= s;
}

static inline ulong3 operator/( ulong3 a, ulong3 b )
{
	return make_ulong3( a.x / b.x, a.y / b.y, a.z / b.z );
}

static inline ulong3 operator/( ulong3 a, ulong s )
{
	return make_ulong3( a.x / s, a.y / s, a.z / s );
}

static inline ulong3 operator/( ulong s, ulong3 a )
{
	return make_ulong3( s / a.x, s / a.y, s / a.z );
}

static inline void operator/=( ulong3& a, ulong s )
{
	a.x /= s; a.y /= s; a.z /= s;
}

static inline ulong3 clamp( ulong3 v, ulong a, ulong b )
{
	ulong3 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );
	r.z = clamp( v.z, a, b );

	return r;
}

static inline ulong3 clamp( ulong3 v, ulong3 a, ulong3 b )
{
	ulong3 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );
	r.z = clamp( v.z, a.z, b.z );

	return r;
}

#endif
