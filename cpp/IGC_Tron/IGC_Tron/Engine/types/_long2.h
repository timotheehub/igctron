
#ifndef _LONG2
#define _LONG2

#include "_long.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline long2 make_long2( long s )
{
	return make_long2( s, s );
}

static inline long2 make_long2( float2 a )
{
	return make_long2( long(a.x), long(a.y) );
}

static inline long2 min( long2 a, long2 b )
{
	long2 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );

	return r;
}

static inline long2 max( long2 a, long2 b )
{
	long2 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );

	return r;
}

static inline long2 operator-( long2 a )
{
	return make_long2( -a.x, -a.y );
}

static inline long2 operator+( long2 a, long2 b )
{
	return make_long2( a.x + b.x, a.y + b.y );
}

static inline void operator+=( long2& a, long2 b )
{
	a.x += b.x; a.y += b.y;
}

static inline long2 operator-( long2 a, long2 b )
{
	return make_long2( a.x - b.x, a.y - b.y );
}

static inline void operator-=( long2& a, long2 b )
{
	a.x -= b.x; a.y -= b.y;
}

static inline long2 operator*( long2 a, long2 b )
{
	return make_long2( a.x * b.x, a.y * b.y );
}

static inline long2 operator*( long2 a, long s )
{
	return make_long2( a.x * s, a.y * s );
}

static inline long2 operator*( long s, long2 a )
{
	return make_long2( a.x * s, a.y * s );
}

static inline void operator*=( long2& a, long s )
{
	a.x *= s; a.y *= s;
}

static inline long2 operator/( long2 a, long2 b )
{
	return make_long2( a.x / b.x, a.y / b.y );
}

static inline long2 operator/( long2 a, long s )
{
	return make_long2( a.x / s, a.y / s );
}

static inline long2 operator/( long s, long2 a )
{
	return make_long2( s / a.x, s / a.y );
}

static inline void operator/=( long2& a, long s )
{
	a.x /= s; a.y /= s;
}

static inline long2 clamp( long2 v, long a, long b )
{
	long2 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );

	return r;
}

static inline long2 clamp( long2 v, long2 a, long2 b )
{
	long2 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );

	return r;
}

static inline long2 abs( long2 v )
{
	return make_long2( abs( v.x ), abs( v.y ) );
}

#endif
