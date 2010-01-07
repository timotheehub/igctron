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

#include "Engine.h"
#include "W32Window.h"
#include "D3DTexture.h"

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

	D3DTexture::D3DTexture( Engine* _engine ) : ITexture( _engine )
	{
		lpTexture = NULL;
	}

	D3DTexture::~D3DTexture()
	{
		if ( lpTexture )
			lpTexture->Release();
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void D3DTexture::update()
	{
		if ( lpTexture )
			lpTexture->Release();

		LPDIRECT3DDEVICE9 lpD3DDevice = ((D3DRenderer*)renderer)->getDevice();

		if ( format == FORMAT_L8 )
			D3DXCreateTexture( lpD3DDevice, width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_L8, D3DPOOL_DEFAULT, (LPDIRECT3DTEXTURE9*)&lpTexture );
		else if ( format == FORMAT_L8A8 )
			D3DXCreateTexture( lpD3DDevice, width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8L8, D3DPOOL_DEFAULT, (LPDIRECT3DTEXTURE9*)&lpTexture );
		else if ( format == FORMAT_R8G8B8 )
			D3DXCreateTexture( lpD3DDevice, width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, (LPDIRECT3DTEXTURE9*)&lpTexture );
		else if ( format == FORMAT_R8G8B8A8 )
			D3DXCreateTexture( lpD3DDevice, width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, (LPDIRECT3DTEXTURE9*)&lpTexture );

		D3DLOCKED_RECT rect;
		lpTexture->LockRect( 0, &rect, NULL, 0 );

		byte* d3d_data = (byte*)rect.pBits;

		int u = rect.Pitch;
		int v = width;

		if ( format == FORMAT_L8 )
		{
			for ( int p = 0 ; p < height ; p++ )
			{
				int i = p * u;
				int j = p * v;

				for ( int q = 0 ; q < width ; q++ )
				{
					d3d_data[i+q] = data[j+q];
				}
			}
		}
		else if ( format == FORMAT_L8A8 )
		{
			for ( int p = 0 ; p < height ; p++ )
			{
				int i = p * u;
				int j = p * v * 2;

				for ( int q = 0 ; q < width ; q++ )
				{
					d3d_data[i+2*q+0] = data[j+2*q+1];
					d3d_data[i+2*q+1] = data[j+2*q+0];
				}
			}
		}
		else if ( format == FORMAT_R8G8B8 )
		{
			for ( int p = 0 ; p < height ; p++ )
			{
				int i = p * u;
				int j = p * v * 3;

				for ( int q = 0 ; q < width ; q++ )
				{
					d3d_data[i+4*q+0] = data[j+3*q+2];
					d3d_data[i+4*q+1] = data[j+3*q+1];
					d3d_data[i+4*q+2] = data[j+3*q+0];
					d3d_data[i+4*q+3] = 0;
				}
			}
		}
		else if ( format == FORMAT_R8G8B8A8 )
		{
			for ( int p = 0 ; p < height ; p++ )
			{
				int i = p * u;
				int j = p * v * 4;

				for ( int q = 0 ; q < width ; q++ )
				{
					d3d_data[i+4*q+0] = data[j+4*q+2];
					d3d_data[i+4*q+1] = data[j+4*q+1];
					d3d_data[i+4*q+2] = data[j+4*q+0];
					d3d_data[i+4*q+3] = data[j+4*q+3];
				}
			}
		}

		lpTexture->UnlockRect(0);

		dirty = false;
	}

	void D3DTexture::bind()
	{
		if ( dirty ) update();

		LPDIRECT3DDEVICE9 lpD3DDevice = ((D3DRenderer*)renderer)->getDevice();

		lpD3DDevice->SetTexture( 0, lpTexture );
	}

	void D3DTexture::unbind()
	{
		LPDIRECT3DDEVICE9 lpD3DDevice = ((D3DRenderer*)renderer)->getDevice();

		lpD3DDevice->SetTexture( 0, NULL );
	}

}

#endif
