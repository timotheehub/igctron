
#ifndef _UCHAR1
#define _UCHAR1

#include "_uchar.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline uchar1 make_uchar1( float1 a )
{
	return make_uchar1( uchar(a.x) );
}

static inline uchar1 min( uchar1 a, uchar1 b )
{
	uchar1 r;

	r.x = min( a.x, b.x );

	return r;
}

static inline uchar1 max( uchar1 a, uchar1 b )
{
	uchar1 r;

	r.x = max( a.x, b.x );

	return r;
}

static inline uchar1 operator-( uchar1 a )
{
	return make_uchar1( -a.x );
}

static inline uchar1 operator+( uchar1 a, uchar1 b )
{
	return make_uchar1( a.x + b.x );
}

static inline void operator+=( uchar1& a, uchar1 b )
{
	a.x += b.x;
}

static inline uchar1 operator-( uchar1 a, uchar1 b )
{
	return make_uchar1( a.x - b.x );
}

static inline void operator-=( uchar1& a, uchar1 b )
{
	a.x -= b.x;
}

static inline uchar1 operator*( uchar1 a, uchar1 b )
{
	return make_uchar1( a.x * b.x );
}

static inline uchar1 operator*( uchar1 a, uchar s )
{
	return make_uchar1( a.x * s );
}

static inline uchar1 operator*( uchar s, uchar1 a )
{
	return make_uchar1( a.x * s );
}

static inline void operator*=( uchar1& a, uchar s )
{
	a.x *= s;
}

static inline uchar1 operator/( uchar1 a, uchar1 b )
{
	return make_uchar1( a.x / b.x );
}

static inline uchar1 operator/( uchar1 a, uchar s )
{
	return make_uchar1( a.x / s );
}

static inline uchar1 operator/( uchar s, uchar1 a )
{
	return make_uchar1( s / a.x );
}

static inline void operator/=( uchar1& a, uchar s )
{
	a.x /= s;
}

static inline uchar1 clamp( uchar1 v, uchar a, uchar b )
{
	uchar1 r;

	r.x = clamp( v.x, a, b );

	return r;
}

static inline uchar1 clamp( uchar1 v, uchar1 a, uchar1 b )
{
	uchar1 r;

	r.x = clamp( v.x, a.x, b.x );

	return r;
}

#endif
