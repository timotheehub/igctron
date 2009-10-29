/**************************************************************************/
/* This file is part of IGC Tron                                          */
/* (c) IGC Software 2009 - 2010                                           */
/* Author : Pierre-Yves GATOUILLAT                                        */
/**************************************************************************/
/* This program is free software: you can redistribute it and/or modify   */
/* it under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                    */
/*                                                                        */
/* This program is distributed in the hope that it will be useful,        */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/* GNU General Public License for more details.                           */
/*                                                                        */
/* You should have received a copy of the GNU General Public License      */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>.  */
/**************************************************************************/

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

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	int IRenderer::toPointX( float _x )
	{
		return (int)(_x * (float)width);
	}

	int IRenderer::toPointY( float _y )
	{
		return (int)(_y * (float)height);
	}

}
