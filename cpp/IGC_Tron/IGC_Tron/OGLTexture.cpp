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
#include "OGLTexture.h"

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

	OGLTexture::OGLTexture( Engine* _engine ) : ITexture( _engine )
	{
		glTexID = 0;
	}

	OGLTexture::~OGLTexture()
	{
		if ( glTexID != 0 )
			glDeleteTextures( 1, &glTexID );
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void OGLTexture::update()
	{
		glEnable( GL_TEXTURE_2D );

		glGenTextures( 1, &glTexID );
		glBindTexture( GL_TEXTURE_2D, glTexID );

		if ( format == FORMAT_L8 )
			glTexImage2D( GL_TEXTURE_2D, 0, GL_LUMINANCE8, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data );
		else if ( format == FORMAT_L8A8 )
			glTexImage2D( GL_TEXTURE_2D, 0, GL_LUMINANCE8_ALPHA8, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data );
		else if ( format == FORMAT_R8G8B8 )
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
		else if ( format == FORMAT_R8G8B8A8 )
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		dirty = false;
	}

	void OGLTexture::bind()
	{
		if ( dirty ) update();

		glEnable( GL_TEXTURE_2D );

		glBindTexture( GL_TEXTURE_2D, glTexID );
	}

	void OGLTexture::unbind()
	{
		glDisable( GL_TEXTURE_2D );
	}

}
