
/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "IRenderer.h"
#include "Engine.h"

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

	IRenderer::IRenderer( Engine* _engine )
	{
		engine = _engine;

		engine->renderer = this;

		fullscreen = false;

		verticalSync = false;

		hardware = true;
	}

	IRenderer::~IRenderer()
	{
		labels.clear();
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	Engine* IRenderer::getEngine()
	{
		return engine;
	}

	void IRenderer::enableFullscreen( int _width, int _height )
	{
		fullscreen = true;
	}

	void IRenderer::disableFullscreen()
	{
		fullscreen = false;
	}

	void IRenderer::enableVSync()
	{
		verticalSync = true;
	}

	void IRenderer::disableVSync()
	{
		verticalSync = false;
	}

	void IRenderer::useHardware()
	{
		hardware = true;
	}

	void IRenderer::useSoftware()
	{
		hardware = false;
	}

	void IRenderer::insertLabel( const string& _text, int _x, int _y,
										float _r, float _g, float _b, float _a )
	{
		Label label = { _text, _x, _y, _r, _g, _b, _a };

		labels.push_back( label );
	}

	void IRenderer::clearForeground()
	{
		labels.clear();
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

}
