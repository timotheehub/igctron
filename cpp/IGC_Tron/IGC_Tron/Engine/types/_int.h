
#ifndef _INT
#define _INT

#include <math.h>

static inline int min( int a, int b )
{
	return a < b ? a : b;
}

static inline int max( int a, int b )
{
	return a > b ? a : b;
}

static inline int __float_as_ordered_int( float f )
{
	int i = *((int*)&f);

	return ( i >= 0 ) ? i : i ^ 0x7FFFFFFF;
}

static inline int clamp( int f, int a, int b )
{
	return max( a, min( f, b ) );
}

#endif
