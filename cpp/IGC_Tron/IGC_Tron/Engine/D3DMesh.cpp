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

#ifdef _WIN32

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "D3DMesh.h"

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

	D3DMesh::D3DMesh( D3DRenderer* _renderer ) : IMesh( _renderer )
	{
		renderer = _renderer;
	}

	D3DMesh::~D3DMesh()
	{
		if ( lpVertexDeclaration )
			lpVertexDeclaration->Release();

		if ( lpIndexBuffer )
			lpIndexBuffer->Release();

		if ( lpVertexBuffer )
			lpVertexBuffer->Release();
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void D3DMesh::update()
	{
		{
			D3DVERTEXELEMENT9 declaration[5];
			
			int offset = 0, k = 0;
			
			if ( hasVertices )
			{
				declaration[k].Stream = 0;
				declaration[k].Offset = offset;
				declaration[k].Type = D3DDECLTYPE_FLOAT3;
				declaration[k].Method = D3DDECLMETHOD_DEFAULT;
				declaration[k].Usage = D3DDECLUSAGE_POSITION;
				declaration[k].UsageIndex = 0;
				
				offset += sizeof(float3); k++;
			}

			if ( hasNormals )
			{
				declaration[k].Stream = 0;
				declaration[k].Offset = offset;
				declaration[k].Type = D3DDECLTYPE_FLOAT3;
				declaration[k].Method = D3DDECLMETHOD_DEFAULT;
				declaration[k].Usage = D3DDECLUSAGE_NORMAL;
				declaration[k].UsageIndex = 0;

				offset += sizeof(float3); k++;
			}

			if ( hasTexcoords )
			{
				declaration[k].Stream = 0;
				declaration[k].Offset = offset;
				declaration[k].Type = D3DDECLTYPE_FLOAT2;
				declaration[k].Method = D3DDECLMETHOD_DEFAULT;
				declaration[k].Usage = D3DDECLUSAGE_TEXCOORD;
				declaration[k].UsageIndex = 0;

				offset += sizeof(float2); k++;
			}

			if ( hasColors )
			{
				declaration[k].Stream = 0;
				declaration[k].Offset = offset;
				declaration[k].Type = D3DDECLTYPE_FLOAT4;
				declaration[k].Method = D3DDECLMETHOD_DEFAULT;
				declaration[k].Usage = D3DDECLUSAGE_COLOR;
				declaration[k].UsageIndex = 0;

				offset += sizeof(float4); k++;
			}

			{
				declaration[k].Stream = 0xFF;
				declaration[k].Offset = 0;
				declaration[k].Type = D3DDECLTYPE_UNUSED;
				declaration[k].Method = 0;
				declaration[k].Usage = 0;
				declaration[k].UsageIndex = 0;
			}

			renderer->getDevice()->CreateVertexDeclaration( declaration, &lpVertexDeclaration );

			D3DXFVFFromDeclarator( declaration, &dwFVF );
		}

		{
			UINT size = vertexCount * D3DXGetFVFVertexSize( dwFVF );

			LPBYTE data = 0;
			UINT offset = 0;

			renderer->getDevice()->CreateVertexBuffer( size, D3DUSAGE_WRITEONLY,
				dwFVF, D3DPOOL_DEFAULT, &lpVertexBuffer, NULL );

			lpVertexBuffer->Lock( 0, size, (void**)&data, 0 );
			
			for ( uint k = 0 ; k < vertexCount ; k++ )
			{
				if ( hasVertices ) { CopyMemory( data+offset, (void*)&vertices[k], sizeof(float3) ); offset += sizeof(float3); }
				if ( hasNormals ) { CopyMemory( data+offset, (void*)&normals[k], sizeof(float3) ); offset += sizeof(float3); }
				if ( hasTexcoords ) { CopyMemory( data+offset, (void*)&texcoords[k], sizeof(float2) ); offset += sizeof(float2); }
				if ( hasColors ) { CopyMemory( data+offset, (void*)&colors[k], sizeof(float4) ); offset += sizeof(float4); }
			}

			lpVertexBuffer->Unlock();
		}

		{
			UINT size = faceCount * sizeof(uint3);

			LPBYTE data = 0;
			UINT offset = 0;

			renderer->getDevice()->CreateIndexBuffer( size, D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX32, D3DPOOL_DEFAULT, &lpIndexBuffer, NULL );

			lpIndexBuffer->Lock( 0, size, (void**)&data, 0 );

			for ( uint k = 0 ; k < faceCount ; k++ )
			{
				CopyMemory( data+offset, (void*)&faces[k], sizeof(uint3) );
				
				offset += sizeof(uint3);
			}

			lpIndexBuffer->Unlock();
		}
	}

	void D3DMesh::render()
	{
		renderer->getDevice()->BeginScene();

		UINT size = D3DXGetFVFVertexSize( dwFVF );

		renderer->getDevice()->SetStreamSource( 0, lpVertexBuffer, 0, size );
		renderer->getDevice()->SetIndices( lpIndexBuffer );

		renderer->getDevice()->SetFVF( dwFVF );

		renderer->getDevice()->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, faceCount );

		renderer->getDevice()->EndScene();
	}

}

#endif
