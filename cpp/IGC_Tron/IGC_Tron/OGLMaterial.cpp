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

#include "Engine.h"
#include "OGLMaterial.h"

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

	OGLMaterial::OGLMaterial( Engine* _engine ) : IMaterial( _engine )
	{
	}

	OGLMaterial::~OGLMaterial()
	{
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void OGLMaterial::update()
	{
		dirty = false;
	}

	void OGLMaterial::bind()
	{
		if ( dirty ) update();

		glEnable( GL_LIGHTING );
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat*)&diffuse );
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat*)&ambient );
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat*)&specular );
		glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, (GLfloat*)&emissive );
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat)power );
	}

	void OGLMaterial::unbind()
	{
		glDisable( GL_LIGHTING );
	}

}
