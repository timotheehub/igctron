
#ifndef _UINT
#define _UINT

#include <math.h>

static inline uint min( uint a, uint b )
{
	return a < b ? a : b;
}

static inline uint max( uint a, uint b )
{
	return a > b ? a : b;
}

static inline uint clamp( uint f, uint a, uint b )
{
	return max( a, min( f, b ) );
}

#endif
