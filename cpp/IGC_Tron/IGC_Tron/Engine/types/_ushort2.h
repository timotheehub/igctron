
#ifndef _USHORT2
#define _USHORT2

#include "_ushort.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline ushort2 make_ushort2( ushort s )
{
	return make_ushort2( s, s );
}

static inline ushort2 make_ushort2( float2 a )
{
	return make_ushort2( ushort(a.x), ushort(a.y) );
}

static inline ushort2 min( ushort2 a, ushort2 b )
{
	ushort2 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );

	return r;
}

static inline ushort2 max( ushort2 a, ushort2 b )
{
	ushort2 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );

	return r;
}

static inline ushort2 operator-( ushort2 a )
{
	return make_ushort2( -a.x, -a.y );
}

static inline ushort2 operator+( ushort2 a, ushort2 b )
{
	return make_ushort2( a.x + b.x, a.y + b.y );
}

static inline void operator+=( ushort2& a, ushort2 b )
{
	a.x += b.x; a.y += b.y;
}

static inline ushort2 operator-( ushort2 a, ushort2 b )
{
	return make_ushort2( a.x - b.x, a.y - b.y );
}

static inline void operator-=( ushort2& a, ushort2 b )
{
	a.x -= b.x; a.y -= b.y;
}

static inline ushort2 operator*( ushort2 a, ushort2 b )
{
	return make_ushort2( a.x * b.x, a.y * b.y );
}

static inline ushort2 operator*( ushort2 a, ushort s )
{
	return make_ushort2( a.x * s, a.y * s );
}

static inline ushort2 operator*( ushort s, ushort2 a )
{
	return make_ushort2( a.x * s, a.y * s );
}

static inline void operator*=( ushort2& a, ushort s )
{
	a.x *= s; a.y *= s;
}

static inline ushort2 operator/( ushort2 a, ushort2 b )
{
	return make_ushort2( a.x / b.x, a.y / b.y );
}

static inline ushort2 operator/( ushort2 a, ushort s )
{
	return make_ushort2( a.x / s, a.y / s );
}

static inline ushort2 operator/( ushort s, ushort2 a )
{
	return make_ushort2( s / a.x, s / a.y );
}

static inline void operator/=( ushort2& a, ushort s )
{
	a.x /= s; a.y /= s;
}

static inline ushort2 clamp( ushort2 v, ushort a, ushort b )
{
	ushort2 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );

	return r;
}

static inline ushort2 clamp( ushort2 v, ushort2 a, ushort2 b )
{
	ushort2 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );

	return r;
}

#endif
