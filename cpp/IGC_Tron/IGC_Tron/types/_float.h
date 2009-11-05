
#ifndef _FLOAT
#define _FLOAT

#include <math.h>

#ifdef _WIN32
static inline float fminf( float a, float b )
{
	return a < b ? a : b;
}

static inline float fmaxf( float a, float b )
{
	return a > b ? a : b;
}
#endif

static inline float rsqrtf( float x )
{
	return 1.0f / sqrtf(x);
}

static inline float __ordered_int_as_float( int i )
{
	int k = ( i >= 0 ) ? i : i ^ 0x7FFFFFFF;

	return *((float*)&k);
}

static inline float lerp( float a, float b, float t )
{
	return a + t * ( b - a );
}

static inline float clamp( float f, float a, float b )
{
	return fmaxf( a, fminf( f, b ) );
}

#endif
