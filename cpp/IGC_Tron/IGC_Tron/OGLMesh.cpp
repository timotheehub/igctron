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
		// TODO : cr�er le VBO
	}

	void OGLMesh::render()
	{
		// TODO : rendre le VBO

		glBegin( GL_TRIANGLES );

		for ( uint k = 0 ; k < faceCount ; k++ )
		{
			uint3 face = faces[k];

			float3 va = vertices[face.x];
			float3 vb = vertices[face.y];
			float3 vc = vertices[face.z];

			float3 na = normals[face.x];
			float3 nb = normals[face.y];
			float3 nc = normals[face.z];

			float4 ca = colors[face.x];
			float4 cb = colors[face.y];
			float4 cc = colors[face.z];

			float2 ta = texcoords[face.x];
			float2 tb = texcoords[face.y];
			float2 tc = texcoords[face.z];

			if ( hasColors ) glColor4f( ca.x, ca.y, ca.z, ca.w );
			if ( hasTexcoords ) glTexCoord2f( ta.x, ta.y );
			if ( hasNormals ) glNormal3f( na.x, na.y, na.z );
			if ( hasVertices ) glVertex3f( va.x, va.y, va.z );

			if ( hasColors ) glColor4f( cb.x, cb.y, cb.z, cb.w );
			if ( hasTexcoords ) glTexCoord2f( tb.x, tb.y );
			if ( hasNormals ) glNormal3f( nb.x, nb.y, nb.z );
			if ( hasVertices ) glVertex3f( vb.x, vb.y, vb.z );

			if ( hasColors ) glColor4f( cc.x, cc.y, cc.z, cc.w );
			if ( hasTexcoords ) glTexCoord2f( tc.x, tc.y );
			if ( hasNormals ) glNormal3f( nc.x, nc.y, nc.z );
			if ( hasVertices ) glVertex3f( vc.x, vc.y, vc.z );
		}

		glEnd();
	}

}
