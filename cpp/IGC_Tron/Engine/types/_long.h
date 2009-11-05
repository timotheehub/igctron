
#ifndef _LONG
#define _LONG

#include <math.h>

static inline long min( long a, long b )
{
	return a < b ? a : b;
}

static inline long max( long a, long b )
{
	return a > b ? a : b;
}

static inline long clamp( long f, long a, long b )
{
	return max( a, min( f, b ) );
}

#endif
