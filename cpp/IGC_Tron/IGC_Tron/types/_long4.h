
#ifndef _LONG4
#define _LONG4

#include "_long.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline long4 make_long4( long s )
{
	return make_long4( s, s, s, s );
}

static inline long4 make_long4( long3 s )
{
	return make_long4( s.x, s.y, s.z, 0 );
}

static inline long4 make_long4( long3 s, long w )
{
	return make_long4( s.x, s.y, s.z, w );
}

static inline long4 make_long4( float4 a )
{
	return make_long4( long(a.x), long(a.y), long(a.z), long(a.w) );
}

static inline long4 min( long4 a, long4 b )
{
	long4 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );
	r.z = min( a.z, b.z );
	r.w = min( a.w, b.w );

	return r;
}

static inline long4 max( long4 a, long4 b )
{
	long4 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );
	r.z = max( a.z, b.z );
	r.w = max( a.w, b.w );

	return r;
}

static inline long4 operator-( long4 a )
{
	return make_long4( -a.x, -a.y, -a.z, -a.w );
}

static inline long4 operator+( long4 a, long4 b )
{
	return make_long4( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w );
}

static inline void operator+=( long4& a, long4 b )
{
	a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w;
}

static inline long4 operator-( long4 a, long4 b )
{
	return make_long4( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w );
}

static inline void operator-=( long4& a, long4 b )
{
	a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w;
}

static inline long4 operator*( long4 a, long4 b )
{
	return make_long4( a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w );
}

static inline long4 operator*( long4 a, long s )
{
	return make_long4( a.x * s, a.y * s, a.z * s, a.w * s );
}

static inline long4 operator*( long s, long4 a )
{
	return make_long4( a.x * s, a.y * s, a.z * s, a.w * s );
}

static inline void operator*=( long4& a, long s )
{
	a.x *= s; a.y *= s; a.z *= s; a.w *= s;
}

static inline long4 operator/( long4 a, long4 b )
{
	return make_long4( a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w );
}

static inline long4 operator/( long4 a, long s )
{
	return make_long4( a.x / s, a.y / s, a.z / s, a.w / s );
}

static inline long4 operator/( long s, long4 a )
{
	return make_long4( s / a.x, s / a.y, s / a.z, s / a.w );
}

static inline void operator/=( long4& a, long s )
{
	a.x /= s; a.y /= s; a.z /= s; a.w /= s;
}

static inline long4 clamp( long4 v, long a, long b )
{
	long4 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );
	r.z = clamp( v.z, a, b );
	r.w = clamp( v.w, a, b );

	return r;
}

static inline long4 clamp( long4 v, long4 a, long4 b )
{
	long4 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );
	r.z = clamp( v.z, a.z, b.z );
	r.w = clamp( v.w, a.w, b.w );

	return r;
}

static inline long4 abs( long4 v )
{
	return make_long4( abs( v.x ), abs( v.y ), abs( v.z ), abs( v.w ) );
}

#endif
