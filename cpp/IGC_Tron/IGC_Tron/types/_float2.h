
#ifndef _FLOAT2
#define _FLOAT2

#include "_float.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline float2 make_float2( float s )
{
	return make_float2( s, s );
}

static inline float2 make_float2( int2 a )
{
	return make_float2( float(a.x), float(a.y) );
}

static inline float2 fminf( float2 a, float2 b )
{
	float2 r;

	r.x = fminf( a.x, b.x );
	r.y = fminf( a.y, b.y );

	return r;
}

static inline float2 fmaxf( float2 a, float2 b )
{
	float2 r;

	r.x = fmaxf( a.x, b.x );
	r.y = fmaxf( a.y, b.y );

	return r;
}

static inline float2 operator-( float2& a )
{
	return make_float2( -a.x, -a.y );
}

static inline float2 operator+( float2 a, float2 b )
{
	return make_float2( a.x + b.x, a.y + b.y );
}

static inline void operator+=( float2& a, float2 b )
{
	a.x += b.x; a.y += b.y;
}

static inline float2 operator-( float2 a, float2 b )
{
	return make_float2( a.x - b.x, a.y - b.y );
}

static inline void operator-=( float2& a, float2 b )
{
	a.x -= b.x; a.y -= b.y;
}

static inline float2 operator*( float2 a, float2 b )
{
	return make_float2( a.x * b.x, a.y * b.y );
}

static inline float2 operator*( float2 a, float s )
{
	return make_float2( a.x * s, a.y * s );
}

static inline float2 operator*( float s, float2 a )
{
	return make_float2( a.x * s, a.y * s );
}

static inline void operator*=( float2& a, float s )
{
	a.x *= s; a.y *= s;
}

static inline float2 operator/( float2 a, float2 b )
{
	return make_float2( a.x / b.x, a.y / b.y );
}

static inline float2 operator/( float2 a, float s )
{
	float inv = 1.0f / s;

	return a * inv;
}

static inline float2 operator/( float s, float2 a )
{
	return make_float2( s / a.x, s / a.y );
}

static inline void operator/=( float2& a, float s )
{
	float inv = 1.0f / s;

	a *= inv;
}

static inline float2 lerp( float2 a, float2 b, float t )
{
	return a + t * ( b - a );
}

static inline float2 clamp( float2 v, float a, float b )
{
	return make_float2( clamp( v.x, a, b ), clamp( v.y, a, b ) );
}

static inline float2 clamp( float2 v, float2 a, float2 b )
{
	return make_float2( clamp( v.x, a.x, b.x ), clamp( v.y, a.y, b.y ) );
}

static inline float dot( float2 a, float2 b )
{ 
	return a.x * b.x + a.y * b.y;
}

static inline float length( float2 v )
{
	return sqrtf( dot( v, v ) );
}

static inline float2 normalize( float2 v )
{
	float inv_len = rsqrtf( dot( v, v ) );

	return v * inv_len;
}

static inline float2 floor( const float2 v )
{
	return make_float2( floor( v.x ), floor( v.y ) );
}

static inline float2 reflect( float2 i, float2 n )
{
	return i - 2.0f * n * dot( n, i );
}

static inline float2 fabs( float2 v )
{
	return make_float2( fabs( v.x ), fabs( v.y ) );
}

#endif
