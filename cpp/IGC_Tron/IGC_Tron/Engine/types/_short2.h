
#ifndef _SHORT2
#define _SHORT2

#include "_short.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline short2 make_short2( short s )
{
	return make_short2( s, s );
}

static inline short2 make_short2( float2 a )
{
	return make_short2( short(a.x), short(a.y) );
}

static inline short2 min( short2 a, short2 b )
{
	short2 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );

	return r;
}

static inline short2 max( short2 a, short2 b )
{
	short2 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );

	return r;
}

static inline short2 operator-( short2 a )
{
	return make_short2( -a.x, -a.y );
}

static inline short2 operator+( short2 a, short2 b )
{
	return make_short2( a.x + b.x, a.y + b.y );
}

static inline void operator+=( short2& a, short2 b )
{
	a.x += b.x; a.y += b.y;
}

static inline short2 operator-( short2 a, short2 b )
{
	return make_short2( a.x - b.x, a.y - b.y );
}

static inline void operator-=( short2& a, short2 b )
{
	a.x -= b.x; a.y -= b.y;
}

static inline short2 operator*( short2 a, short2 b )
{
	return make_short2( a.x * b.x, a.y * b.y );
}

static inline short2 operator*( short2 a, short s )
{
	return make_short2( a.x * s, a.y * s );
}

static inline short2 operator*( short s, short2 a )
{
	return make_short2( a.x * s, a.y * s );
}

static inline void operator*=( short2& a, short s )
{
	a.x *= s; a.y *= s;
}

static inline short2 operator/( short2 a, short2 b )
{
	return make_short2( a.x / b.x, a.y / b.y );
}

static inline short2 operator/( short2 a, short s )
{
	return make_short2( a.x / s, a.y / s );
}

static inline short2 operator/( short s, short2 a )
{
	return make_short2( s / a.x, s / a.y );
}

static inline void operator/=( short2& a, short s )
{
	a.x /= s; a.y /= s;
}

static inline short2 clamp( short2 v, short a, short b )
{
	short2 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );

	return r;
}

static inline short2 clamp( short2 v, short2 a, short2 b )
{
	short2 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );

	return r;
}

static inline short2 abs( short2 v )
{
	return make_short2( abs( v.x ), abs( v.y ) );
}

#endif
