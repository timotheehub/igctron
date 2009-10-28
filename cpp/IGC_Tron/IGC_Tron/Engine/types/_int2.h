
#ifndef _INT2
#define _INT2

#include "_int.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline int2 make_int2( int s )
{
	return make_int2( s, s );
}

static inline int2 make_int2( float2 a )
{
	return make_int2( int(a.x), int(a.y) );
}

static inline int2 min( int2 a, int2 b )
{
	int2 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );

	return r;
}

static inline int2 max( int2 a, int2 b )
{
	int2 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );

	return r;
}

static inline int2 operator-( int2 a )
{
	return make_int2( -a.x, -a.y );
}

static inline int2 operator+( int2 a, int2 b )
{
	return make_int2( a.x + b.x, a.y + b.y );
}

static inline void operator+=( int2& a, int2 b )
{
	a.x += b.x; a.y += b.y;
}

static inline int2 operator-( int2 a, int2 b )
{
	return make_int2( a.x - b.x, a.y - b.y );
}

static inline void operator-=( int2& a, int2 b )
{
	a.x -= b.x; a.y -= b.y;
}

static inline int2 operator*( int2 a, int2 b )
{
	return make_int2( a.x * b.x, a.y * b.y );
}

static inline int2 operator*( int2 a, int s )
{
	return make_int2( a.x * s, a.y * s );
}

static inline int2 operator*( int s, int2 a )
{
	return make_int2( a.x * s, a.y * s );
}

static inline void operator*=( int2& a, int s )
{
	a.x *= s; a.y *= s;
}

static inline int2 operator/( int2 a, int2 b )
{
	return make_int2( a.x / b.x, a.y / b.y );
}

static inline int2 operator/( int2 a, int s )
{
	return make_int2( a.x / s, a.y / s );
}

static inline int2 operator/( int s, int2 a )
{
	return make_int2( s / a.x, s / a.y );
}

static inline void operator/=( int2& a, int s )
{
	a.x /= s; a.y /= s;
}

static inline int2 clamp( int2 v, int a, int b )
{
	int2 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );

	return r;
}

static inline int2 clamp( int2 v, int2 a, int2 b )
{
	int2 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );

	return r;
}

static inline int2 abs( int2 v )
{
	return make_int2( abs( v.x ), abs( v.y ) );
}

#endif
