
#ifndef _SHORT
#define _SHORT

#include <math.h>

static inline short min( short a, short b )
{
	return a < b ? a : b;
}

static inline short max( short a, short b )
{
	return a > b ? a : b;
}

static inline short clamp( short f, short a, short b )
{
	return max( a, min( f, b ) );
}

#endif
