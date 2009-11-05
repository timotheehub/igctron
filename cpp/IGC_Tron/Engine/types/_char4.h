
#ifndef _CHAR4
#define _CHAR4

#include "_char.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline char4 make_char4( char s )
{
	return make_char4( s, s, s, s );
}

static inline char4 make_char4( char3 s )
{
	return make_char4( s.x, s.y, s.z, 0 );
}

static inline char4 make_char4( char3 s, char w )
{
	return make_char4( s.x, s.y, s.z, w );
}

static inline char4 make_char4( float4 a )
{
	return make_char4( char(a.x), char(a.y), char(a.z), char(a.w) );
}

static inline char4 min( char4 a, char4 b )
{
	char4 r;

	r.x = min( a.x, b.x );
	r.y = min( a.y, b.y );
	r.z = min( a.z, b.z );
	r.w = min( a.w, b.w );

	return r;
}

static inline char4 max( char4 a, char4 b )
{
	char4 r;

	r.x = max( a.x, b.x );
	r.y = max( a.y, b.y );
	r.z = max( a.z, b.z );
	r.w = max( a.w, b.w );

	return r;
}

static inline char4 operator-( char4 a )
{
	return make_char4( -a.x, -a.y, -a.z, -a.w );
}

static inline char4 operator+( char4 a, char4 b )
{
	return make_char4( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w );
}

static inline void operator+=( char4& a, char4 b )
{
	a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w;
}

static inline char4 operator-( char4 a, char4 b )
{
	return make_char4( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w );
}

static inline void operator-=( char4& a, char4 b )
{
	a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w;
}

static inline char4 operator*( char4 a, char4 b )
{
	return make_char4( a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w );
}

static inline char4 operator*( char4 a, char s )
{
	return make_char4( a.x * s, a.y * s, a.z * s, a.w * s );
}

static inline char4 operator*( char s, char4 a )
{
	return make_char4( a.x * s, a.y * s, a.z * s, a.w * s );
}

static inline void operator*=( char4& a, char s )
{
	a.x *= s; a.y *= s; a.z *= s; a.w *= s;
}

static inline char4 operator/( char4 a, char4 b )
{
	return make_char4( a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w );
}

static inline char4 operator/( char4 a, char s )
{
	return make_char4( a.x / s, a.y / s, a.z / s, a.w / s );
}

static inline char4 operator/( char s, char4 a )
{
	return make_char4( s / a.x, s / a.y, s / a.z, s / a.w );
}

static inline void operator/=( char4& a, char s )
{
	a.x /= s; a.y /= s; a.z /= s; a.w /= s;
}

static inline char4 clamp( char4 v, char a, char b )
{
	char4 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );
	r.z = clamp( v.z, a, b );
	r.w = clamp( v.w, a, b );

	return r;
}

static inline char4 clamp( char4 v, char4 a, char4 b )
{
	char4 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );
	r.z = clamp( v.z, a.z, b.z );
	r.w = clamp( v.w, a.w, b.w );

	return r;
}

static inline char4 abs( char4 v )
{
	return make_char4( abs( v.x ), abs( v.y ), abs( v.z ), abs( v.w ) );
}

#endif
