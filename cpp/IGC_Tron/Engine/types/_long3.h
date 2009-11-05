
#ifndef _LONG3
#define _LONG3

#include "_long.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline long3 make_long3( long s )
{
	return make_long3( s, s, s );
}

static inline long3 make_long3( long2 s )
{
	return make_long3( s.x, s.y, 0 );
}

static inline long3 make_long3( long2 s, long w )
{
	return make_long3( s.x, s.y, w );
}

static inline long3 make_long3( float3 a )
{
	return make_long3( long(a.x), long(a.y), long(a.z) );
}

static inline long3 min( long3 a, long3 b )
{
	long3 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );
	r.z = min( a.z, b.z );

	return r;
}

static inline long3 max( long3 a, long3 b )
{
	long3 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );
	r.z = max( a.z, b.z );

	return r;
}

static inline long3 operator-( long3 a )
{
	return make_long3( -a.x, -a.y, -a.z );
}

static inline long3 operator+( long3 a, long3 b )
{
	return make_long3( a.x + b.x, a.y + b.y, a.z + b.z );
}

static inline void operator+=( long3& a, long3 b )
{
	a.x += b.x; a.y += b.y; a.z += b.z;
}

static inline long3 operator-( long3 a, long3 b )
{
	return make_long3( a.x - b.x, a.y - b.y, a.z - b.z );
}

static inline void operator-=( long3& a, long3 b )
{
	a.x -= b.x; a.y -= b.y; a.z -= b.z;
}

static inline long3 operator*( long3 a, long3 b )
{
	return make_long3( a.x * b.x, a.y * b.y, a.z * b.z );
}

static inline long3 operator*( long3 a, long s )
{
	return make_long3( a.x * s, a.y * s, a.z * s );
}

static inline long3 operator*( long s, long3 a )
{
	return make_long3( a.x * s, a.y * s, a.z * s );
}

static inline void operator*=( long3& a, long s )
{
	a.x *= s; a.y *= s; a.z *= s;
}

static inline long3 operator/( long3 a, long3 b )
{
	return make_long3( a.x / b.x, a.y / b.y, a.z / b.z );
}

static inline long3 operator/( long3 a, long s )
{
	return make_long3( a.x / s, a.y / s, a.z / s );
}

static inline long3 operator/( long s, long3 a )
{
	return make_long3( s / a.x, s / a.y, s / a.z );
}

static inline void operator/=( long3& a, long s )
{
	a.x /= s; a.y /= s; a.z /= s;
}

static inline long3 clamp( long3 v, long a, long b )
{
	long3 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );
	r.z = clamp( v.z, a, b );

	return r;
}

static inline long3 clamp( long3 v, long3 a, long3 b )
{
	long3 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );
	r.z = clamp( v.z, a.z, b.z );

	return r;
}

static inline long3 abs( long3 v )
{
	return make_long3( abs( v.x ), abs( v.y ), abs( v.z ) );
}

#endif
