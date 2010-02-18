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

#include "IMaterial.h"

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

	IMaterial::IMaterial( Engine* _engine )
	{
		engine = _engine;

		renderer = engine->getRenderer();

		diffuse = make_float4( 1.0f );
		ambient = make_float4( 1.0f );
		specular = make_float4( 1.0f );
		emissive = make_float4( 1.0f );
		power = 1.0f;

		dirty = true;
	}

	IMaterial::~IMaterial()
	{
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	Engine* IMaterial::getEngine()
	{
		return engine;
	}

	IRenderer* IMaterial::getRenderer()
	{
		return renderer;
	}

/***********************************************************************************/
/** METHODES PRIVEES                                                              **/
/***********************************************************************************/

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

}
