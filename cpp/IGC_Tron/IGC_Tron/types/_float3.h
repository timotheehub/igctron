
#ifndef _FLOAT3
#define _FLOAT3

#include "_float.h"

#include "vector_types.h"
#include "vector_functions.h"

static inline float3 make_float3( float s )
{
	return make_float3( s, s, s );
}

static inline float3 make_float3( float2 a )
{
	return make_float3( a.x, a.y, 0.0f );
}

static inline float3 make_float3( float2 a, float s )
{
	return make_float3( a.x, a.y, s );
}

static inline float3 make_float3( float4 a )
{
	return make_float3( a.x, a.y, a.z );
}

static inline float3 make_float3( int3 a )
{
	return make_float3( float(a.x), float(a.y), float(a.z) );
}

static inline float3 operator-( float3& a )
{
	return make_float3( -a.x, -a.y, -a.z );
}

static inline float3 fminf( float3 a, float4 b )
{
	float3 r;

	r.x = fminf( a.x, b.x );
	r.y = fminf( a.y, b.y );
	r.z = fminf( a.z, b.z );

	return r;
}

static inline float3 fmaxf( float3 a, float4 b )
{
	float3 r;

	r.x = fmaxf( a.x, b.x );
	r.y = fmaxf( a.y, b.y );
	r.z = fmaxf( a.z, b.z );

	return r;
}

static inline float3 fminf( float3 a, float3 b )
{
	float3 r;

	r.x = fminf( a.x, b.x );
	r.y = fminf( a.y, b.y );
	r.z = fminf( a.z, b.z );

	return r;
}

static inline float3 fmaxf( float3 a, float3 b )
{
	float3 r;

	r.x = fmaxf( a.x, b.x );
	r.y = fmaxf( a.y, b.y );
	r.z = fmaxf( a.z, b.z );

	return r;
}

static inline float3 operator+( float3 a, float3 b )
{
	return make_float3( a.x + b.x, a.y + b.y, a.z + b.z );
}

static inline float3 operator+( float3 a, float b )
{
	return make_float3( a.x + b, a.y + b, a.z + b );
}

static inline void operator+=( float3& a, float3 b )
{
	a.x += b.x; a.y += b.y; a.z += b.z;
}

static inline float3 operator-( float3 a, float3 b )
{
	return make_float3( a.x - b.x, a.y - b.y, a.z - b.z );
}

static inline float3 operator-( float3 a, float b )
{
	return make_float3( a.x - b, a.y - b, a.z - b );
}

static inline void operator-=( float3& a, float3 b )
{
	a.x -= b.x; a.y -= b.y; a.z -= b.z;
}

static inline float3 operator*( float3 a, float3 b )
{
	return make_float3( a.x * b.x, a.y * b.y, a.z * b.z );
}

static inline float3 operator*( float3 a, float s )
{
	return make_float3( a.x * s, a.y * s, a.z * s );
}

static inline float3 operator*( float s, float3 a )
{
	return make_float3( a.x * s, a.y * s, a.z * s );
}

static inline void operator*=( float3& a, float s )
{
	a.x *= s; a.y *= s; a.z *= s;
}

static inline float3 operator/( float3 a, float3 b )
{
	return make_float3( a.x / b.x, a.y / b.y, a.z / b.z );
}

static inline float3 operator/( float3 a, float s )
{
	float inv = 1.0f / s;

	return a * inv;
}

static inline float3 operator/( float s, float3 a )
{
	return make_float3( s / a.x, s / a.y, s / a.z );
}

static inline void operator/=( float3& a, float s )
{
	float inv = 1.0f / s;

	a *= inv;
}

static inline float3 lerp( float3 a, float3 b, float t )
{
	return a + t * ( b - a );
}

static inline float3 clamp( float3 v, float a, float b )
{
	float3 r;

	r.x = clamp( v.x, a, b );
	r.y = clamp( v.y, a, b );
	r.z = clamp( v.z, a, b );

	return r;
}

static inline float3 clamp( float3 v, float3 a, float3 b )
{
	float3 r;

	r.x = clamp( v.x, a.x, b.x );
	r.y = clamp( v.y, a.y, b.y );
	r.z = clamp( v.z, a.z, b.z );

	return r;
}

static inline float dot( float3 a, float3 b )
{ 
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline float3 cross( float3 a, float3 b )
{ 
	float3 r;

	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;

	return r;
}

static inline float length( float3 v )
{
	return sqrtf( dot( v, v ) );
}

static inline float3 normalize( float3 v )
{
	float inv_len = rsqrtf( dot( v, v ) );

	return v * inv_len;
}

static inline float3 floor( float3 v )
{
	return make_float3( floor( v.x ), floor( v.y ), floor( v.z ) );
}

static inline float3 reflect( float3 i, float3 n )
{
	return i - 2.0f * n * dot( n, i );
}

static inline float3 fabs( float3 v )
{
	return make_float3( fabs( v.x ), fabs( v.y ), fabs( v.z ) );
}

#endif
