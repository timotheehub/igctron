
#ifdef _WIN32

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "D3DCamera.h"

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

	D3DCamera::D3DCamera( D3DRenderer* _renderer ) : ICamera( _renderer )
	{
		renderer = _renderer;
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void D3DCamera::bind()
	{
		if ( dirty ) update();

		renderer->getDevice()->SetTransform( D3DTS_VIEW, (D3DMATRIX*)&matView );
		renderer->getDevice()->SetTransform( D3DTS_PROJECTION, (D3DMATRIX*)&matProj );
	}

}

#endif
