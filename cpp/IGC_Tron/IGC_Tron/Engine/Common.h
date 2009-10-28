
#ifndef _COMMON
#define _COMMON

#pragma warning (disable : 4251)

/***********************************************************************************/
/** DEFINITIONS                                                                   **/
/***********************************************************************************/

#define USE_WIN32
// #define USE_X11

// #define USE_DIRECT3D
#define USE_OPENGL

#ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x400
#endif

#define DIRECTINPUT_VERSION  0x0800

/***********************************************************************************/
/** TYPES                                                                         **/
/***********************************************************************************/

typedef unsigned long long qword;
typedef unsigned int dword;
typedef unsigned short word;
typedef long long wide;
typedef unsigned long long uwide;
typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned char byte;

namespace IGC
{
#ifdef USE_WIN32
	typedef class W32Window Window;
#endif
#ifdef USE_X11
	typedef class X11Window Window;
#endif
#ifdef USE_DIRECT3D
	typedef class D3DRenderer Renderer;
	typedef class D3DCamera Camera;
	typedef class D3DMesh Mesh;
	typedef class D3DModel Model;
#endif
#ifdef USE_OPENGL
	typedef class OGLRenderer Renderer;
	typedef class OGLCamera Camera;
	typedef class OGLMesh Mesh;
	typedef class OGLModel Model;
#endif
}

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include <assert.h>

#include "types/_char.h"
#include "types/_char1.h"
#include "types/_char2.h"
#include "types/_char3.h"
#include "types/_char4.h"

#include "types/_uchar.h"
#include "types/_uchar1.h"
#include "types/_uchar2.h"
#include "types/_uchar3.h"
#include "types/_uchar4.h"

#include "types/_short.h"
#include "types/_short1.h"
#include "types/_short2.h"
#include "types/_short3.h"
#include "types/_short4.h"

#include "types/_ushort.h"
#include "types/_ushort1.h"
#include "types/_ushort2.h"
#include "types/_ushort3.h"
#include "types/_ushort4.h"

#include "types/_int.h"
#include "types/_int1.h"
#include "types/_int2.h"
#include "types/_int3.h"
#include "types/_int4.h"

#include "types/_uint.h"
#include "types/_uint1.h"
#include "types/_uint2.h"
#include "types/_uint3.h"
#include "types/_uint4.h"

#include "types/_long.h"
#include "types/_long1.h"
#include "types/_long2.h"
#include "types/_long3.h"
#include "types/_long4.h"

#include "types/_ulong.h"
#include "types/_ulong1.h"
#include "types/_ulong2.h"
#include "types/_ulong3.h"
#include "types/_ulong4.h"

#include "types/_float.h"
#include "types/_float1.h"
#include "types/_float2.h"
#include "types/_float3.h"
#include "types/_float4.h"
#include "types/_float4x4.h"

#ifdef _WIN32
	#include <windows.h>
	#include <stdio.h>
#else
	#include <stdarg.h>
	#include <stdio.h>
	#include <string.h>
#endif

/***********************************************************************************/
/** CONSTANTES                                                                    **/
/***********************************************************************************/

#define PI (3.14159265359f)
#define DEG2RAD (0.01745329252f)
#define RAD2DEG (57.2957795131f)
#define INF (3.4028234E38f)

/***********************************************************************************/
/** MACROS                                                                        **/
/***********************************************************************************/

#define irand( min, max ) rand() % (max - min) + min
#define frand( min, max ) (double)rand() / (double)RAND_MAX * (max - min) + min

/***********************************************************************************/
/** FONCTIONS                                                                     **/
/***********************************************************************************/

inline static void _assert( bool predicate, char* file, int line, char* message )
{
	if ( !predicate )
	{
		printf( "Error in %s, line %d : %s\n\n", file, line, message );

		system( "pause" );

		exit( -1 );
	}
}

/***********************************************************************************/

#endif
