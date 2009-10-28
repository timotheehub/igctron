
#ifndef _UCHAR
#define _UCHAR

#include <math.h>

static inline uchar min( uchar a, uchar b )
{
	return a < b ? a : b;
}

static inline uchar max( uchar a, uchar b )
{
	return a > b ? a : b;
}

static inline uchar clamp( uchar f, uchar a, uchar b )
{
	return max( a, min( f, b ) );
}

#endif
