
#ifndef _FLOAT1
#define _FLOAT1

#include "_float.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline float1 make_float1( int1 a )
{
	return make_float1( float(a.x) );
}

static inline float1 fminf( float1 a, float1 b )
{
	float1 r;

	r.x = fminf( a.x, b.x );

	return r;
}

static inline float1 fmaxf( float1 a, float1 b )
{
	float1 r;

	r.x = fmaxf( a.x, b.x );

	return r;
}

static inline float1 operator-( float1& a )
{
	return make_float1( -a.x );
}

static inline float1 operator+( float1 a, float1 b )
{
	return make_float1( a.x + b.x );
}

static inline void operator+=( float1& a, float1 b )
{
	a.x += b.x;
}

static inline float1 operator-( float1 a, float1 b )
{
	return make_float1( a.x - b.x );
}

static inline void operator-=( float1& a, float1 b )
{
	a.x -= b.x;
}

static inline float1 operator*( float1 a, float1 b )
{
	return make_float1( a.x * b.x );
}

static inline float1 operator*( float1 a, float s )
{
	return make_float1( a.x * s );
}

static inline float1 operator*( float s, float1 a )
{
	return make_float1( a.x * s );
}

static inline void operator*=( float1& a, float s )
{
	a.x *= s;
}

static inline float1 operator/( float1 a, float1 b )
{
	return make_float1( a.x / b.x );
}

static inline float1 operator/( float1 a, float s )
{
	return make_float1( a.x / s );
}

static inline float1 operator/( float s, float1 a )
{
	return make_float1( s / a.x );
}

static inline void operator/=( float1& a, float s )
{
	a.x /= s;
}

static inline float1 lerp( float1 a, float1 b, float t )
{
	return a + t * ( b - a );
}

static inline float1 clamp( float1 v, float a, float b )
{
	return make_float1( clamp( v.x, a, b ) );
}

static inline float1 clamp( float1 v, float1 a, float1 b )
{
	return make_float1( clamp( v.x, a.x, b.x ) );
}

static inline float dot( float1 a, float1 b )
{ 
	return a.x * b.x;
}

static inline float length( float1 v )
{
	return sqrtf( dot( v, v ) );
}

static inline float1 normalize( float1 v )
{
	return make_float1( 1.0f );
}

static inline float1 floor( const float1 v )
{
	return make_float1( floor( v.x ) );
}

static inline float1 reflect( float1 i, float1 n )
{
	return i - 2.0f * n * dot( n, i );
}

static inline float1 fabs( float1 v )
{
	return make_float1( fabs( v.x ) );
}

#endif
