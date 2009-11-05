
#ifndef _ULONG1
#define _ULONG1

#include "_ulong.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline ulong1 make_ulong1( float1 a )
{
	return make_ulong1( ulong(a.x) );
}

static inline ulong1 min( ulong1 a, ulong1 b )
{
	ulong1 r;

	r.x = min( a.x, b.x );

	return r;
}

static inline ulong1 max( ulong1 a, ulong1 b )
{
	ulong1 r;

	r.x = max( a.x, b.x );

	return r;
}

static inline ulong1 operator+( ulong1 a, ulong1 b )
{
	return make_ulong1( a.x + b.x );
}

static inline void operator+=( ulong1& a, ulong1 b )
{
	a.x += b.x;
}

static inline ulong1 operator-( ulong1 a, ulong1 b )
{
	return make_ulong1( a.x - b.x );
}

static inline void operator-=( ulong1& a, ulong1 b )
{
	a.x -= b.x;
}

static inline ulong1 operator*( ulong1 a, ulong1 b )
{
	return make_ulong1( a.x * b.x );
}

static inline ulong1 operator*( ulong1 a, ulong s )
{
	return make_ulong1( a.x * s );
}

static inline ulong1 operator*( ulong s, ulong1 a )
{
	return make_ulong1( a.x * s );
}

static inline void operator*=( ulong1& a, ulong s )
{
	a.x *= s;
}

static inline ulong1 operator/( ulong1 a, ulong1 b )
{
	return make_ulong1( a.x / b.x );
}

static inline ulong1 operator/( ulong1 a, ulong s )
{
	return make_ulong1( a.x / s );
}

static inline ulong1 operator/( ulong s, ulong1 a )
{
	return make_ulong1( s / a.x );
}

static inline void operator/=( ulong1& a, ulong s )
{
	a.x /= s;
}

static inline ulong1 clamp( ulong1 v, ulong a, ulong b )
{
	ulong1 r;

	r.x = clamp( v.x, a, b );

	return r;
}

static inline ulong1 clamp( ulong1 v, ulong1 a, ulong1 b )
{
	ulong1 r;

	r.x = clamp( v.x, a.x, b.x );

	return r;
}

#endif
