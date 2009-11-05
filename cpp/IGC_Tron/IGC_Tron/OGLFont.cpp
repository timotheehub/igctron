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
#include "W32Window.h"
#include "OGLFont.h"

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

	OGLFont::OGLFont( Engine* _engine ) : IFont( _engine )
	{
		glFontList = 0;
	}

	OGLFont::~OGLFont()
	{
		if ( glFontList != 0 )
			glDeleteLists( glFontList, 96 );
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void OGLFont::update()
	{
#ifdef _WIN32
		W32Window* window = (W32Window*)renderer->getEngine()->getWindow();

		HWND hWnd = window->getHandle();

		HDC hDC = CreateCompatibleDC( GetDC( hWnd ) );

		HFONT font;
		HFONT oldfont;

		glFontList = glGenLists( 96 );

		SHORT fontSize = -MulDiv( size, GetDeviceCaps( hDC, LOGPIXELSY ), 72 );
		SHORT fontWeight = bold ? FW_BOLD : FW_NORMAL;
		BOOL fontItalic = italic ? TRUE : FALSE;

		font = CreateFont( fontSize, 0, 0, 0, fontWeight, fontItalic, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE | DEFAULT_PITCH, name );					

		oldfont = (HFONT)SelectObject( hDC, font );
		wglUseFontBitmaps( hDC, 32, 96, glFontList );
		SelectObject( hDC, oldfont );
		DeleteObject( font );
#else
		glFontList = glGenLists(96);

		X11Window* window = (X11Window*)renderer->getEngine()->getWindow();

		/* TODO : Comment on sp�cifie la police qu'on veut sans passer par une chaine de caract�res immonde ? */
		XFontStruct* font = XLoadQueryFont(window->getDisplay() , "-*-helvetica-bold-r-normal--24-*-*-*-p-*-iso8859-1" );

		if ( font == NULL )
		{
			font = XLoadQueryFont( window->getDisplay(), "fixed" );

			_assert( font != NULL, __FILE__, __LINE__, "OGLRenderer::initialize() : Unable to load any font." );
		}

		glXUseXFont( font->fid, 32, 96, glFontList );

		XFreeFont( window->getDisplay(), font );
#endif

		dirty = false;
	}

	void OGLFont::bind()
	{
		if ( dirty ) update();

		((OGLRenderer*)renderer)->setFont( glFontList );
	}

}
