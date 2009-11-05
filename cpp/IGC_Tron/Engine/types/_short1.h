
#ifndef _SHORT1
#define _SHORT1

#include "_short.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline short1 make_short1( float1 a )
{
	return make_short1( short(a.x) );
}

static inline short1 min( short1 a, short1 b )
{
	short1 r;

	r.x = min( a.x, b.x );

	return r;
}

static inline short1 max( short1 a, short1 b )
{
	short1 r;

	r.x = max( a.x, b.x );

	return r;
}

static inline short1 operator-( short1 a )
{
	return make_short1( -a.x );
}

static inline short1 operator+( short1 a, short1 b )
{
	return make_short1( a.x + b.x );
}

static inline void operator+=( short1& a, short1 b )
{
	a.x += b.x;
}

static inline short1 operator-( short1 a, short1 b )
{
	return make_short1( a.x - b.x );
}

static inline void operator-=( short1& a, short1 b )
{
	a.x -= b.x;
}

static inline short1 operator*( short1 a, short1 b )
{
	return make_short1( a.x * b.x );
}

static inline short1 operator*( short1 a, short s )
{
	return make_short1( a.x * s );
}

static inline short1 operator*( short s, short1 a )
{
	return make_short1( a.x * s );
}

static inline void operator*=( short1& a, short s )
{
	a.x *= s;
}

static inline short1 operator/( short1 a, short1 b )
{
	return make_short1( a.x / b.x );
}

static inline short1 operator/( short1 a, short s )
{
	return make_short1( a.x / s );
}

static inline short1 operator/( short s, short1 a )
{
	return make_short1( s / a.x );
}

static inline void operator/=( short1& a, short s )
{
	a.x /= s;
}

static inline short1 clamp( short1 v, short a, short b )
{
	short1 r;

	r.x = clamp( v.x, a, b );

	return r;
}

static inline short1 clamp( short1 v, short1 a, short1 b )
{
	short1 r;

	r.x = clamp( v.x, a.x, b.x );

	return r;
}

static inline short1 abs( short1 v )
{
	return make_short1( abs( v.x ) );
}

#endif
