
#ifndef _USHORT
#define _USHORT

#include <math.h>

static inline ushort min( ushort a, ushort b )
{
	return a < b ? a : b;
}

static inline ushort max( ushort a, ushort b )
{
	return a > b ? a : b;
}

static inline ushort clamp( ushort f, ushort a, ushort b )
{
	return max( a, min( f, b ) );
}

#endif
