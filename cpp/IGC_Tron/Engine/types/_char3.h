
#ifndef _CHAR3
#define _CHAR3

#include "_char.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline char3 make_char3( char s )
{
	return make_char3( s, s, s );
}

static inline char3 make_char3( char2 s )
{
	return make_char3( s.x, s.y, 0 );
}

static inline char3 make_char3( char2 s, char w )
{
	return make_char3( s.x, s.y, w );
}

static inline char3 make_char3( float3 a )
{
	return make_char3( char(a.x), char(a.y), char(a.z) );
}

static inline char3 min( char3 a, char3 b )
{
	char3 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );
	r.z = min( a.z, b.z );

	return r;
}

static inline char3 max( char3 a, char3 b )
{
	char3 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );
	r.z = max( a.z, b.z );

	return r;
}

static inline char3 operator-( char3 a )
{
	return make_char3( -a.x, -a.y, -a.z );
}

static inline char3 operator+( char3 a, char3 b )
{
	return make_char3( a.x + b.x, a.y + b.y, a.z + b.z );
}

static inline void operator+=( char3& a, char3 b )
{
	a.x += b.x; a.y += b.y; a.z += b.z;
}

static inline char3 operator-( char3 a, char3 b )
{
	return make_char3( a.x - b.x, a.y - b.y, a.z - b.z );
}

static inline void operator-=( char3& a, char3 b )
{
	a.x -= b.x; a.y -= b.y; a.z -= b.z;
}

static inline char3 operator*( char3 a, char3 b )
{
	return make_char3( a.x * b.x, a.y * b.y, a.z * b.z );
}

static inline char3 operator*( char3 a, char s )
{
	return make_char3( a.x * s, a.y * s, a.z * s );
}

static inline char3 operator*( char s, char3 a )
{
	return make_char3( a.x * s, a.y * s, a.z * s );
}

static inline void operator*=( char3& a, char s )
{
	a.x *= s; a.y *= s; a.z *= s;
}

static inline char3 operator/( char3 a, char3 b )
{
	return make_char3( a.x / b.x, a.y / b.y, a.z / b.z );
}

static inline char3 operator/( char3 a, char s )
{
	return make_char3( a.x / s, a.y / s, a.z / s );
}

static inline char3 operator/( char s, char3 a )
{
	return make_char3( s / a.x, s / a.y, s / a.z );
}

static inline void operator/=( char3& a, char s )
{
	a.x /= s; a.y /= s; a.z /= s;
}

static inline char3 clamp( char3 v, char a, char b )
{
	char3 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );
	r.z = clamp( v.z, a, b );

	return r;
}

static inline char3 clamp( char3 v, char3 a, char3 b )
{
	char3 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );
	r.z = clamp( v.z, a.z, b.z );

	return r;
}

static inline char3 abs( char3 v )
{
	return make_char3( abs( v.x ), abs( v.y ), abs( v.z ) );
}

#endif
