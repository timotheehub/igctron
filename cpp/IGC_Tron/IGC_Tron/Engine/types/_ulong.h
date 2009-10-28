
#ifndef _ULONG
#define _ULONG

#include <math.h>

static inline ulong min( ulong a, ulong b )
{
	return a < b ? a : b;
}

static inline ulong max( ulong a, ulong b )
{
	return a > b ? a : b;
}

static inline ulong clamp( ulong f, ulong a, ulong b )
{
	return max( a, min( f, b ) );
}

#endif
