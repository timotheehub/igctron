
#ifndef _UINT4
#define _UINT4

#include "_uint.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline uint4 make_uint4( uint s )
{
	return make_uint4( s, s, s, s );
}

static inline uint4 make_uint4( uint3 s )
{
	return make_uint4( s.x, s.y, s.z, 0 );
}

static inline uint4 make_uint4( uint3 s, uint w )
{
	return make_uint4( s.x, s.y, s.z, w );
}

static inline uint4 make_uint4( float4 a )
{
	return make_uint4( uint(a.x), uint(a.y), uint(a.z), uint(a.w) );
}

static inline uint4 min( uint4 a, uint4 b )
{
	uint4 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );
	r.z = min( a.z, b.z );
	r.w = min( a.w, b.w );

	return r;
}

static inline uint4 max( uint4 a, uint4 b )
{
	uint4 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );
	r.z = max( a.z, b.z );
	r.w = max( a.w, b.w );

	return r;
}

static inline uint4 operator+( uint4 a, uint4 b )
{
	return make_uint4( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w );
}

static inline void operator+=( uint4& a, uint4 b )
{
	a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w;
}

static inline uint4 operator-( uint4 a, uint4 b )
{
	return make_uint4( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w );
}

static inline void operator-=( uint4& a, uint4 b )
{
	a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w;
}

static inline uint4 operator*( uint4 a, uint4 b )
{
	return make_uint4( a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w );
}

static inline uint4 operator*( uint4 a, uint s )
{
	return make_uint4( a.x * s, a.y * s, a.z * s, a.w * s );
}

static inline uint4 operator*( uint s, uint4 a )
{
	return make_uint4( a.x * s, a.y * s, a.z * s, a.w * s );
}

static inline void operator*=( uint4& a, uint s )
{
	a.x *= s; a.y *= s; a.z *= s; a.w *= s;
}

static inline uint4 operator/( uint4 a, uint4 b )
{
	return make_uint4( a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w );
}

static inline uint4 operator/( uint4 a, uint s )
{
	return make_uint4( a.x / s, a.y / s, a.z / s, a.w / s );
}

static inline uint4 operator/( uint s, uint4 a )
{
	return make_uint4( s / a.x, s / a.y, s / a.z, s / a.w );
}

static inline void operator/=( uint4& a, uint s )
{
	a.x /= s; a.y /= s; a.z /= s; a.w /= s;
}

static inline uint4 clamp( uint4 v, uint a, uint b )
{
	uint4 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );
	r.z = clamp( v.z, a, b );
	r.w = clamp( v.w, a, b );

	return r;
}

static inline uint4 clamp( uint4 v, uint4 a, uint4 b )
{
	uint4 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );
	r.z = clamp( v.z, a.z, b.z );
	r.w = clamp( v.w, a.w, b.w );

	return r;
}

#endif
