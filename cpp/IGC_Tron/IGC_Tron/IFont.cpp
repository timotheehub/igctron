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

#include "IFont.h"

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

	IFont::IFont( Engine* _engine )
	{
		engine = _engine;

		renderer = engine->getRenderer();

		name = (char*)malloc( 8 * sizeof(char) );
		strcpy( name, "Verdana" );

		size = 12;

		bold = false;
		italic = false;

		dirty = true;
	}

	IFont::~IFont()
	{
		if ( name ) free( name );
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	Engine* IFont::getEngine()
	{
		return engine;
	}

	IRenderer* IFont::getRenderer()
	{
		return renderer;
	}

	void IFont::setName( const char* _name )
	{
		name = (char*)realloc( name, (strlen( _name ) + 1) * sizeof(char) );
		strcpy( name, _name );

		dirty = true;
	}

	void IFont::setSize( int _size )
	{
		size = _size;

		dirty = true;
	}

	void IFont::setBold( bool _bold )
	{
		bold = _bold;

		dirty = true;
	}

	void IFont::setItalic( bool _italic )
	{
		italic = _italic;

		dirty = true;
	}

}
