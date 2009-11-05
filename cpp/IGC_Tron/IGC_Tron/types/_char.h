
#ifndef _CHAR
#define _CHAR

#include <math.h>
#include <stdlib.h>

static inline char min( char a, char b )
{
	return a < b ? a : b;
}

static inline char max( char a, char b )
{
	return a > b ? a : b;
}

static inline char clamp( char f, char a, char b )
{
	return max( a, min( f, b ) );
}

#endif
