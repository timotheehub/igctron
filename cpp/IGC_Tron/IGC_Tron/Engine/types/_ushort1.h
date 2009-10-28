
#ifndef _USHORT1
#define _USHORT1

#include "_ushort.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline ushort1 make_ushort1( float1 a )
{
	return make_ushort1( ushort(a.x) );
}

static inline ushort1 min( ushort1 a, ushort1 b )
{
	ushort1 r;

	r.x = min( a.x, b.x );

	return r;
}

static inline ushort1 max( ushort1 a, ushort1 b )
{
	ushort1 r;

	r.x = max( a.x, b.x );

	return r;
}

static inline ushort1 operator-( ushort1 a )
{
	return make_ushort1( -a.x );
}

static inline ushort1 operator+( ushort1 a, ushort1 b )
{
	return make_ushort1( a.x + b.x );
}

static inline void operator+=( ushort1& a, ushort1 b )
{
	a.x += b.x;
}

static inline ushort1 operator-( ushort1 a, ushort1 b )
{
	return make_ushort1( a.x - b.x );
}

static inline void operator-=( ushort1& a, ushort1 b )
{
	a.x -= b.x;
}

static inline ushort1 operator*( ushort1 a, ushort1 b )
{
	return make_ushort1( a.x * b.x );
}

static inline ushort1 operator*( ushort1 a, ushort s )
{
	return make_ushort1( a.x * s );
}

static inline ushort1 operator*( ushort s, ushort1 a )
{
	return make_ushort1( a.x * s );
}

static inline void operator*=( ushort1& a, ushort s )
{
	a.x *= s;
}

static inline ushort1 operator/( ushort1 a, ushort1 b )
{
	return make_ushort1( a.x / b.x );
}

static inline ushort1 operator/( ushort1 a, ushort s )
{
	return make_ushort1( a.x / s );
}

static inline ushort1 operator/( ushort s, ushort1 a )
{
	return make_ushort1( s / a.x );
}

static inline void operator/=( ushort1& a, ushort s )
{
	a.x /= s;
}

static inline ushort1 clamp( ushort1 v, ushort a, ushort b )
{
	ushort1 r;

	r.x = clamp( v.x, a, b );

	return r;
}

static inline ushort1 clamp( ushort1 v, ushort1 a, ushort1 b )
{
	ushort1 r;

	r.x = clamp( v.x, a.x, b.x );

	return r;
}

#endif
