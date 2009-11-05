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

#include "IMesh.h"

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

	IMesh::IMesh( Engine* _engine )
	{
		engine = _engine;

		renderer = engine->getRenderer();

		box.reset();

		hasVertices = false;
		hasNormals = false;
		hasColors = false;
		hasTexcoords = false;

		vertices = NULL;
		normals = NULL;
		colors = NULL;
		texcoords = NULL;
		faces = NULL;

		vertexCount = 0;
		faceCount = 0;
	}

	IMesh::~IMesh()
	{
		if ( faces )
			free( faces );

		if ( texcoords )
			free( texcoords );

		if ( colors )
			free( colors );

		if ( normals )
			free( normals );

		if ( vertices )
			free( vertices );
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	Engine* IMesh::getEngine()
	{
		return engine;
	}

	IRenderer* IMesh::getRenderer()
	{
		return renderer;
	}

	void IMesh::setVertexCount( uint _count )
	{
		if ( hasVertices )
			vertices = (float3*)realloc( vertices, _count * sizeof(float3) );

		if ( hasNormals )
			normals = (float3*)realloc( normals, _count * sizeof(float3) );
	
		if ( hasColors )
			colors = (float4*)realloc( colors, _count * sizeof(float4) );
	
		if ( hasTexcoords )
			texcoords = (float2*)realloc( texcoords, _count * sizeof(float2) );

		vertexCount = _count;
	}

	uint IMesh::getVertexCount()
	{
		return vertexCount;
	}

	void IMesh::setFaceCount( uint _count )
	{
		faces = (uint3*)realloc( faces, _count * sizeof(uint3) );

		faceCount = _count;
	}

	uint IMesh::getFaceCount()
	{
		return faceCount;
	}

	float3* IMesh::getVertexPointer()
	{
		return vertices;
	}

	float3* IMesh::getNormalPointer()
	{
		return normals;
	}

	float4* IMesh::getColorPointer()
	{
		return colors;
	}

	float2* IMesh::getTexcoordPointer()
	{
		return texcoords;
	}

	uint3* IMesh::getFacePointer()
	{
		return faces;
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void IMesh::createCube( float width, float height, float depth )
	{
		hasVertices = true;

		setVertexCount( 8 );

		setVertex( 0, -0.5f * width, -0.5f * height, -0.5f * depth );
		setVertex( 1, -0.5f * width, -0.5f * height, +0.5f * depth );
		setVertex( 2, -0.5f * width, +0.5f * height, -0.5f * depth );
		setVertex( 3, -0.5f * width, +0.5f * height, +0.5f * depth );
		setVertex( 4, +0.5f * width, -0.5f * height, -0.5f * depth );
		setVertex( 5, +0.5f * width, -0.5f * height, +0.5f * depth );
		setVertex( 6, +0.5f * width, +0.5f * height, -0.5f * depth );
		setVertex( 7, +0.5f * width, +0.5f * height, +0.5f * depth );

		setFaceCount( 12 );

		setFace(  0, 0, 1, 2 );
		setFace(  1, 3, 2, 1 );
		setFace(  2, 6, 5, 4 );
		setFace(  3, 5, 6, 7 );

		setFace(  4, 4, 1, 0 );
		setFace(  5, 1, 4, 5 );
		setFace(  6, 2, 3, 6 );
		setFace(  7, 7, 6, 3 );

		setFace(  8, 0, 2, 4 );
		setFace(  9, 6, 4, 2 );
		setFace( 10, 5, 3, 1 );
		setFace( 11, 3, 5, 7 );
	}

}