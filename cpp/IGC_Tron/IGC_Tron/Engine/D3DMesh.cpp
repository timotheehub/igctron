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

	D3DMesh::D3DMesh( Engine* _engine ) : IMesh( _engine )
	{
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
		LPDIRECT3DDEVICE9 lpD3DDevice = ((D3DRenderer*)renderer)->getDevice();

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

			if ( hasColors )
			{
				declaration[k].Stream = 0;
				declaration[k].Offset = offset;
				declaration[k].Type = D3DDECLTYPE_D3DCOLOR;
				declaration[k].Method = D3DDECLMETHOD_DEFAULT;
				declaration[k].Usage = D3DDECLUSAGE_COLOR;
				declaration[k].UsageIndex = 0;

				offset += sizeof(dword); k++;
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

			{
				declaration[k].Stream = 0xFF;
				declaration[k].Offset = 0;
				declaration[k].Type = D3DDECLTYPE_UNUSED;
				declaration[k].Method = 0;
				declaration[k].Usage = 0;
				declaration[k].UsageIndex = 0;
			}

			lpD3DDevice->CreateVertexDeclaration( declaration, &lpVertexDeclaration );

			D3DXFVFFromDeclarator( declaration, &dwFVF );
		}

		{
			UINT size = vertexCount * D3DXGetFVFVertexSize( dwFVF );

			LPBYTE data = 0;
			UINT offset = 0;

			lpD3DDevice->CreateVertexBuffer( size, D3DUSAGE_WRITEONLY, dwFVF,
												D3DPOOL_DEFAULT, &lpVertexBuffer, NULL );

			lpVertexBuffer->Lock( 0, size, (void**)&data, 0 );
			
			for ( uint k = 0 ; k < vertexCount ; k++ )
			{
				if ( hasVertices )
				{
					CopyMemory( data+offset, (void*)&vertices[k], sizeof(float3) );

					offset += sizeof(float3);
				}

				if ( hasNormals )
				{
					CopyMemory( data+offset, (void*)&normals[k], sizeof(float3) );
					
					offset += sizeof(float3);
				}

				if ( hasColors )
				{
					dword color = (dword)( (((int)(colors[k].x * 255.0f)&0xff)<<24) | (((int)(colors[k].y * 255.0f)&0xff)<<16) | (((int)(colors[k].z * 255.0f)&0xff)<<8) | ((int)(colors[k].w * 255.0f)&0xff));

					CopyMemory( data+offset, (void*)&color, sizeof(dword) );

					offset += sizeof(dword);
				}

				if ( hasTexcoords )
				{
					CopyMemory( data+offset, (void*)&texcoords[k], sizeof(float2) );
					
					offset += sizeof(float2);
				}
			}

			lpVertexBuffer->Unlock();
		}

		{
			UINT size = faceCount * sizeof(uint3);

			LPBYTE data = 0;
			UINT offset = 0;

			lpD3DDevice->CreateIndexBuffer( size, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32,
													D3DPOOL_DEFAULT, &lpIndexBuffer, NULL );

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
		LPDIRECT3DDEVICE9 lpD3DDevice = ((D3DRenderer*)renderer)->getDevice();

		lpD3DDevice->BeginScene();

		UINT size = D3DXGetFVFVertexSize( dwFVF );

		lpD3DDevice->SetStreamSource( 0, lpVertexBuffer, 0, size );
		lpD3DDevice->SetIndices( lpIndexBuffer );

		lpD3DDevice->SetFVF( dwFVF );

		lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, faceCount );

		lpD3DDevice->EndScene();
	}

}

#endif
