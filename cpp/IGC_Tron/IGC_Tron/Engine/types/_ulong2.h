
#ifndef _ULONG2
#define _ULONG2

#include "_ulong.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline ulong2 make_ulong2( ulong s )
{
	return make_ulong2( s, s );
}

static inline ulong2 make_ulong2( float2 a )
{
	return make_ulong2( ulong(a.x), ulong(a.y) );
}

static inline ulong2 min( ulong2 a, ulong2 b )
{
	ulong2 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );

	return r;
}

static inline ulong2 max( ulong2 a, ulong2 b )
{
	ulong2 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );

	return r;
}

static inline ulong2 operator+( ulong2 a, ulong2 b )
{
	return make_ulong2( a.x + b.x, a.y + b.y );
}

static inline void operator+=( ulong2& a, ulong2 b )
{
	a.x += b.x; a.y += b.y;
}

static inline ulong2 operator-( ulong2 a, ulong2 b )
{
	return make_ulong2( a.x - b.x, a.y - b.y );
}

static inline void operator-=( ulong2& a, ulong2 b )
{
	a.x -= b.x; a.y -= b.y;
}

static inline ulong2 operator*( ulong2 a, ulong2 b )
{
	return make_ulong2( a.x * b.x, a.y * b.y );
}

static inline ulong2 operator*( ulong2 a, ulong s )
{
	return make_ulong2( a.x * s, a.y * s );
}

static inline ulong2 operator*( ulong s, ulong2 a )
{
	return make_ulong2( a.x * s, a.y * s );
}

static inline void operator*=( ulong2& a, ulong s )
{
	a.x *= s; a.y *= s;
}

static inline ulong2 operator/( ulong2 a, ulong2 b )
{
	return make_ulong2( a.x / b.x, a.y / b.y );
}

static inline ulong2 operator/( ulong2 a, ulong s )
{
	return make_ulong2( a.x / s, a.y / s );
}

static inline ulong2 operator/( ulong s, ulong2 a )
{
	return make_ulong2( s / a.x, s / a.y );
}

static inline void operator/=( ulong2& a, ulong s )
{
	a.x /= s; a.y /= s;
}

static inline ulong2 clamp( ulong2 v, ulong a, ulong b )
{
	ulong2 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );

	return r;
}

static inline ulong2 clamp( ulong2 v, ulong2 a, ulong2 b )
{
	ulong2 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );

	return r;
}

#endif
