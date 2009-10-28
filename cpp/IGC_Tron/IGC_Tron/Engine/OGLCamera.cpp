
#ifdef _WIN32

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "OGLCamera.h"

/***********************************************************************************/
/** DEBUG                                                                         **/
/***********************************************************************************/

#include "Debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***********************************************************************************/

namespace IGC
{

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	OGLCamera::OGLCamera( OGLRenderer* _renderer ) : ICamera( _renderer )
	{
		renderer = _renderer;
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void OGLCamera::bind()
	{
		if ( dirty ) update();

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glLoadMatrixf( (GLfloat*)&matProj );

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glLoadMatrixf( (GLfloat*)&matView );
	}

}

#endif
