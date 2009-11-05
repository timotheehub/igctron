
#ifndef _SHORT3
#define _SHORT3

#include "_short.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline short3 make_short3( short s )
{
	return make_short3( s, s, s );
}

static inline short3 make_short3( short2 s )
{
	return make_short3( s.x, s.y, 0 );
}

static inline short3 make_short3( short2 s, short w )
{
	return make_short3( s.x, s.y, w );
}

static inline short3 make_short3( float3 a )
{
	return make_short3( short(a.x), short(a.y), short(a.z) );
}

static inline short3 min( short3 a, short3 b )
{
	short3 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );
	r.z = min( a.z, b.z );

	return r;
}

static inline short3 max( short3 a, short3 b )
{
	short3 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );
	r.z = max( a.z, b.z );

	return r;
}

static inline short3 operator-( short3 a )
{
	return make_short3( -a.x, -a.y, -a.z );
}

static inline short3 operator+( short3 a, short3 b )
{
	return make_short3( a.x + b.x, a.y + b.y, a.z + b.z );
}

static inline void operator+=( short3& a, short3 b )
{
	a.x += b.x; a.y += b.y; a.z += b.z;
}

static inline short3 operator-( short3 a, short3 b )
{
	return make_short3( a.x - b.x, a.y - b.y, a.z - b.z );
}

static inline void operator-=( short3& a, short3 b )
{
	a.x -= b.x; a.y -= b.y; a.z -= b.z;
}

static inline short3 operator*( short3 a, short3 b )
{
	return make_short3( a.x * b.x, a.y * b.y, a.z * b.z );
}

static inline short3 operator*( short3 a, short s )
{
	return make_short3( a.x * s, a.y * s, a.z * s );
}

static inline short3 operator*( short s, short3 a )
{
	return make_short3( a.x * s, a.y * s, a.z * s );
}

static inline void operator*=( short3& a, short s )
{
	a.x *= s; a.y *= s; a.z *= s;
}

static inline short3 operator/( short3 a, short3 b )
{
	return make_short3( a.x / b.x, a.y / b.y, a.z / b.z );
}

static inline short3 operator/( short3 a, short s )
{
	return make_short3( a.x / s, a.y / s, a.z / s );
}

static inline short3 operator/( short s, short3 a )
{
	return make_short3( s / a.x, s / a.y, s / a.z );
}

static inline void operator/=( short3& a, short s )
{
	a.x /= s; a.y /= s; a.z /= s;
}

static inline short3 clamp( short3 v, short a, short b )
{
	short3 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );
	r.z = clamp( v.z, a, b );

	return r;
}

static inline short3 clamp( short3 v, short3 a, short3 b )
{
	short3 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );
	r.z = clamp( v.z, a.z, b.z );

	return r;
}

static inline short3 abs( short3 v )
{
	return make_short3( abs( v.x ), abs( v.y ), abs( v.z ) );
}

#endif
