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
#include "D3DFont.h"

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

	D3DFont::D3DFont( Engine* _engine ) : IFont( _engine )
	{
		lpFont = NULL;
	}

	D3DFont::~D3DFont()
	{
		if ( lpFont )
			lpFont->Release();
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void D3DFont::update()
	{
		W32Window* window = (W32Window*)renderer->getEngine()->getWindow();

		HWND hWnd = window->getHandle();

		HDC hDC = CreateCompatibleDC( GetDC( hWnd ) );

		SHORT fontSize = -MulDiv( size, GetDeviceCaps( hDC, LOGPIXELSY ), 72 );
		SHORT fontWeight = bold ? FW_BOLD : FW_NORMAL;
		BOOL fontItalic = italic ? TRUE : FALSE;

		LPDIRECT3DDEVICE9 lpD3DDevice = ((D3DRenderer*)renderer)->getDevice();

		if( FAILED( D3DXCreateFont( lpD3DDevice, fontSize, 0, fontWeight, 0, fontItalic, DEFAULT_CHARSET,
							OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, name, &lpFont ) ) )
			_assert( false, __FILE__, __LINE__, "D3DFont::update() : Unable to create Direct3D font." );

		dirty = false;
	}

	void D3DFont::bind()
	{
		if ( dirty ) update();

		((D3DRenderer*)renderer)->setFont( lpFont );
	}

}

#endif
