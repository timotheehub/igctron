
#ifndef _UINT2
#define _UINT2

#include "_uint.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline uint2 make_uint2( uint s )
{
	return make_uint2( s, s );
}

static inline uint2 make_uint2( float2 a )
{
	return make_uint2( uint(a.x), uint(a.y) );
}

static inline uint2 min( uint2 a, uint2 b )
{
	uint2 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );

	return r;
}

static inline uint2 max( uint2 a, uint2 b )
{
	uint2 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );

	return r;
}

static inline uint2 operator+( uint2 a, uint2 b )
{
	return make_uint2( a.x + b.x, a.y + b.y );
}

static inline void operator+=( uint2& a, uint2 b )
{
	a.x += b.x; a.y += b.y;
}

static inline uint2 operator-( uint2 a, uint2 b )
{
	return make_uint2( a.x - b.x, a.y - b.y );
}

static inline void operator-=( uint2& a, uint2 b )
{
	a.x -= b.x; a.y -= b.y;
}

static inline uint2 operator*( uint2 a, uint2 b )
{
	return make_uint2( a.x * b.x, a.y * b.y );
}

static inline uint2 operator*( uint2 a, uint s )
{
	return make_uint2( a.x * s, a.y * s );
}

static inline uint2 operator*( uint s, uint2 a )
{
	return make_uint2( a.x * s, a.y * s );
}

static inline void operator*=( uint2& a, uint s )
{
	a.x *= s; a.y *= s;
}

static inline uint2 operator/( uint2 a, uint2 b )
{
	return make_uint2( a.x / b.x, a.y / b.y );
}

static inline uint2 operator/( uint2 a, uint s )
{
	return make_uint2( a.x / s, a.y / s );
}

static inline uint2 operator/( uint s, uint2 a )
{
	return make_uint2( s / a.x, s / a.y );
}

static inline void operator/=( uint2& a, uint s )
{
	a.x /= s; a.y /= s;
}

static inline uint2 clamp( uint2 v, uint a, uint b )
{
	uint2 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );

	return r;
}

static inline uint2 clamp( uint2 v, uint2 a, uint2 b )
{
	uint2 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );

	return r;
}

#endif
