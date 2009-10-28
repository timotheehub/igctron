
#ifndef _INT3
#define _INT3

#include "_int.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline int3 make_int3( int s )
{
	return make_int3( s, s, s );
}

static inline int3 make_int3( int2 s )
{
	return make_int3( s.x, s.y, 0 );
}

static inline int3 make_int3( int2 s, int w )
{
	return make_int3( s.x, s.y, w );
}

static inline int3 make_int3( float3 a )
{
	return make_int3( int(a.x), int(a.y), int(a.z) );
}

static inline int3 min( int3 a, int3 b )
{
	int3 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );
	r.z = min( a.z, b.z );

	return r;
}

static inline int3 max( int3 a, int3 b )
{
	int3 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );
	r.z = max( a.z, b.z );

	return r;
}

static inline int3 operator-( int3 a )
{
	return make_int3( -a.x, -a.y, -a.z );
}

static inline int3 operator+( int3 a, int3 b )
{
	return make_int3( a.x + b.x, a.y + b.y, a.z + b.z );
}

static inline void operator+=( int3& a, int3 b )
{
	a.x += b.x; a.y += b.y; a.z += b.z;
}

static inline int3 operator-( int3 a, int3 b )
{
	return make_int3( a.x - b.x, a.y - b.y, a.z - b.z );
}

static inline void operator-=( int3& a, int3 b )
{
	a.x -= b.x; a.y -= b.y; a.z -= b.z;
}

static inline int3 operator*( int3 a, int3 b )
{
	return make_int3( a.x * b.x, a.y * b.y, a.z * b.z );
}

static inline int3 operator*( int3 a, int s )
{
	return make_int3( a.x * s, a.y * s, a.z * s );
}

static inline int3 operator*( int s, int3 a )
{
	return make_int3( a.x * s, a.y * s, a.z * s );
}

static inline void operator*=( int3& a, int s )
{
	a.x *= s; a.y *= s; a.z *= s;
}

static inline int3 operator/( int3 a, int3 b )
{
	return make_int3( a.x / b.x, a.y / b.y, a.z / b.z );
}

static inline int3 operator/( int3 a, int s )
{
	return make_int3( a.x / s, a.y / s, a.z / s );
}

static inline int3 operator/( int s, int3 a )
{
	return make_int3( s / a.x, s / a.y, s / a.z );
}

static inline void operator/=( int3& a, int s )
{
	a.x /= s; a.y /= s; a.z /= s;
}

static inline int3 clamp( int3 v, int a, int b )
{
	int3 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );
	r.z = clamp( v.z, a, b );

	return r;
}

static inline int3 clamp( int3 v, int3 a, int3 b )
{
	int3 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );
	r.z = clamp( v.z, a.z, b.z );

	return r;
}

static inline int3 abs( int3 v )
{
	return make_int3( abs( v.x ), abs( v.y ), abs( v.z ) );
}

#endif
