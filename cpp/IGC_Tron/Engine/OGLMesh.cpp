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

#include "OGLMesh.h"

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

	OGLMesh::OGLMesh( Engine* _engine ) : IMesh( _engine )
	{
	}

	OGLMesh::~OGLMesh()
	{
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void OGLMesh::update()
	{
		// TODO : créer le VBO
	}

	void OGLMesh::render()
	{
		// TODO : rendre le VBO

		glDisable( GL_TEXTURE_2D ); // TEMP
		glColor3f( 0.0f, 0.0f, 0.0f );  // TEMP

		glBegin( GL_TRIANGLES );

		for ( uint k = 0 ; k < faceCount ; k++ )
		{
			uint3 face = faces[k];

			float3 a = vertices[face.x];
			float3 b = vertices[face.y];
			float3 c = vertices[face.z];

			glVertex3f( a.x, a.y, a.z );
			glVertex3f( b.x, b.y, b.z );
			glVertex3f( c.x, c.y, c.z );
		}

		glEnd();
	}

}
