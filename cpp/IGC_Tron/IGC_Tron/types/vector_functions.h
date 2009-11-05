
#ifndef _VECTOR_FUNCTIONS
#define _VECTOR_FUNCTIONS

#include "vector_types.h"

static inline char1 make_char1( signed char x )
{
	char1 t; t.x = x; return t;
}

static inline uchar1 make_uchar1( unsigned char x )
{
	uchar1 t; t.x = x; return t;
}

static inline char2 make_char2( signed char x, signed char y )
{
	char2 t; t.x = x; t.y = y; return t;
}

static inline uchar2 make_uchar2( unsigned char x, unsigned char y )
{
	uchar2 t; t.x = x; t.y = y; return t;
}

static inline char3 make_char3( signed char x, signed char y, signed char z )
{
	char3 t; t.x = x; t.y = y; t.z = z; return t;
}

static inline uchar3 make_uchar3( unsigned char x, unsigned char y, unsigned char z )
{
	uchar3 t; t.x = x; t.y = y; t.z = z; return t;
}

static inline char4 make_char4( signed char x, signed char y, signed char z, signed char w )
{
	char4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t;
}

static inline uchar4 make_uchar4( unsigned char x, unsigned char y, unsigned char z, unsigned char w )
{
	uchar4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t;
}

static inline short1 make_short1( short x )
{
	short1 t; t.x = x; return t;
}

static inline ushort1 make_ushort1( unsigned short x )
{
	ushort1 t; t.x = x; return t;
}

static inline short2 make_short2( short x, short y )
{
	short2 t; t.x = x; t.y = y; return t;
}

static inline ushort2 make_ushort2( unsigned short x, unsigned short y )
{
	ushort2 t; t.x = x; t.y = y; return t;
}

static inline short3 make_short3( short x,short y, short z )
{ 
	short3 t; t.x = x; t.y = y; t.z = z; return t;
}

static inline ushort3 make_ushort3( unsigned short x, unsigned short y, unsigned short z )
{
	ushort3 t; t.x = x; t.y = y; t.z = z; return t;
}

static inline short4 make_short4( short x, short y, short z, short w )
{
	short4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t;
}

static inline ushort4 make_ushort4( unsigned short x, unsigned short y, unsigned short z, unsigned short w )
{
	ushort4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t;
}

static inline int1 make_int1( int x )
{
	int1 t; t.x = x; return t;
}

static inline uint1 make_uint1( unsigned int x )
{
	uint1 t; t.x = x; return t;
}

static inline int2 make_int2( int x, int y )
{
	int2 t; t.x = x; t.y = y; return t;
}

static inline uint2 make_uint2( unsigned int x, unsigned int y )
{
	uint2 t; t.x = x; t.y = y; return t;
}

static inline int3 make_int3( int x, int y, int z )
{
	int3 t; t.x = x; t.y = y; t.z = z; return t;
}

static inline uint3 make_uint3( unsigned int x, unsigned int y, unsigned int z )
{
	uint3 t; t.x = x; t.y = y; t.z = z; return t;
}

static inline int4 make_int4( int x, int y, int z, int w )
{
	int4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t;
}

static inline uint4 make_uint4( unsigned int x, unsigned int y, unsigned int z, unsigned int w )
{
	uint4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t;
}

static inline long1 make_long1( long int x )
{
	long1 t; t.x = x; return t;
}

static inline ulong1 make_ulong1( unsigned long int x )
{
	ulong1 t; t.x = x; return t;
}

static inline long2 make_long2( long int x, long int y )
{
	long2 t; t.x = x; t.y = y; return t;
}

static inline ulong2 make_ulong2( unsigned long int x, unsigned long int y )
{
	ulong2 t; t.x = x; t.y = y; return t;
}

static inline long3 make_long3( long int x, long int y, long int z )
{
	long3 t; t.x = x; t.y = y; t.z = z; return t;
}

static inline ulong3 make_ulong3( unsigned long int x, unsigned long int y, unsigned long int z )
{
	ulong3 t; t.x = x; t.y = y; t.z = z; return t;
}

static inline long4 make_long4( long int x, long int y, long int z, long int w )
{
	long4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t;
}

static inline ulong4 make_ulong4( unsigned long int x, unsigned long int y, unsigned long int z, unsigned long int w )
{
	ulong4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t;
}

static inline float1 make_float1( float x )
{
	float1 t; t.x = x; return t;
}

static inline float2 make_float2( float x, float y )
{
	float2 t; t.x = x; t.y = y; return t;
}

static inline float3 make_float3( float x, float y, float z )
{
	float3 t; t.x = x; t.y = y; t.z = z; return t;
}

static inline float4 make_float4( float x, float y, float z, float w )
{
	float4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t;
}

#endif
