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

#include "IWindow.h"
#include "Engine.h"

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

	IWindow::IWindow( Engine* _engine )
	{
		engine = _engine;

		engine->window = this;

		setLeft();
		setTop();
		setWidth();
		setHeight();

		visible = false;

		title = (char*)malloc( 4 * sizeof(char) );
		strcpy( title, "IGC" );

		keyboardContext = KC_NONE;
		mouseContext = MC_NONE;
	}

	IWindow::~IWindow()
	{
		if ( title ) free( title );

		keyUpCallbacks.clear();
		keyDownCallbacks.clear();

		mouseMoveCallbacks.clear();
		mouseUpCallbacks.clear();
		mouseDownCallbacks.clear();
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	Engine* IWindow::getEngine()
	{
		return engine;
	}

	void IWindow::setTitle( char* _title )
	{
		title = (char*)realloc( title, (strlen( _title ) + 1) * sizeof(char) );
		strcpy( title, _title );
	}

	void IWindow::setLeft( int _value )
	{
		left = _value;
	}

	int IWindow::getLeft()
	{
		return left;
	}

	void IWindow::setTop( int _value )
	{
		top = _value;
	}

	int IWindow::getTop()
	{
		return top;
	}

	void IWindow::setWidth( int _value )
	{
		width = _value;
	}

	int IWindow::getWidth()
	{
		return width;
	}

	void IWindow::setHeight( int _value )
	{
		height = _value;
	}

	int IWindow::getHeight()
	{
		return height;
	}

	int IWindow::getInnerWidth()
	{
		return innerWidth;
	}

	int IWindow::getInnerHeight()
	{
		return innerHeight;
	}

	bool IWindow::isVisible()
	{
		return visible;
	}

	bool IWindow::isActive()
	{
		return active;
	}

	void IWindow::registerCloseCallback( LPCLOSECALLBACK _callback )
	{
		closeCallbacks.push_back( _callback );
	}

	void IWindow::unregisterCloseCallback( LPCLOSECALLBACK _callback )
	{
		if ( visible == false ) return;

		for ( vector<LPCLOSECALLBACK>::iterator it = closeCallbacks.begin() ; it != closeCallbacks.end() ; ++it )
		{
			if ( *it == _callback ) closeCallbacks.erase( it );
		}
	}

	void IWindow::registerKeyUpCallback( LPKEYUPCALLBACK _callback )
	{
		keyUpCallbacks.push_back( _callback );
	}

	void IWindow::unregisterKeyUpCallback( LPKEYUPCALLBACK _callback )
	{
		if ( visible == false ) return;

		for ( vector<LPKEYUPCALLBACK>::iterator it = keyUpCallbacks.begin() ; it != keyUpCallbacks.end() ; ++it )
		{
			if ( *it == _callback ) keyUpCallbacks.erase( it );
		}
	}

	void IWindow::registerKeyDownCallback( LPKEYDOWNCALLBACK _callback )
	{
		keyDownCallbacks.push_back( _callback );
	}

	void IWindow::unregisterKeyDownCallback( LPKEYDOWNCALLBACK _callback )
	{
		if ( visible == false ) return;

		for ( vector<LPKEYDOWNCALLBACK>::iterator it = keyDownCallbacks.begin() ; it != keyDownCallbacks.end() ; ++it )
		{
			if ( *it == _callback ) keyDownCallbacks.erase( it );
		}
	}

	void IWindow::registerMouseMoveCallback( LPMOUSEMOVECALLBACK _callback )
	{
		mouseMoveCallbacks.push_back( _callback );
	}

	void IWindow::unregisterMouseMoveCallback( LPMOUSEMOVECALLBACK _callback )
	{
		if ( visible == false ) return;

		for ( vector<LPMOUSEMOVECALLBACK>::iterator it = mouseMoveCallbacks.begin() ; it != mouseMoveCallbacks.end() ; ++it )
		{
			if ( *it == _callback ) mouseMoveCallbacks.erase( it );
		}
	}

	void IWindow::registerMouseUpCallback( LPMOUSEUPCALLBACK _callback )
	{
		mouseUpCallbacks.push_back( _callback );
	}

	void IWindow::unregisterMouseUpCallback( LPMOUSEUPCALLBACK _callback )
	{
		if ( visible == false ) return;

		for ( vector<LPMOUSEUPCALLBACK>::iterator it = mouseUpCallbacks.begin() ; it != mouseUpCallbacks.end() ; ++it )
		{
			if ( *it == _callback ) mouseUpCallbacks.erase( it );
		}
	}

	void IWindow::registerMouseDownCallback( LPMOUSEDOWNCALLBACK _callback )
	{
		mouseDownCallbacks.push_back( _callback );
	}

	void IWindow::unregisterMouseDownCallback( LPMOUSEDOWNCALLBACK _callback )
	{
		if ( visible == false ) return;

		for ( vector<LPMOUSEDOWNCALLBACK>::iterator it = mouseDownCallbacks.begin() ; it != mouseDownCallbacks.end() ; ++it )
		{
			if ( *it == _callback ) mouseDownCallbacks.erase( it );
		}
	}

/***********************************************************************************/
/** EVENEMENTS                                                                    **/
/***********************************************************************************/

	void IWindow::onClose()
	{
		for ( vector<LPCLOSECALLBACK>::iterator it = closeCallbacks.begin() ; it != closeCallbacks.end() ; ++it )
		{
			LPCLOSECALLBACK Callback = *it;

			Callback();
		}

		active = false;
	}

	void IWindow::onKeyUp( int _keyCode )
	{
		for ( vector<LPKEYUPCALLBACK>::iterator it = keyUpCallbacks.begin() ; it != keyUpCallbacks.end() ; ++it )
		{
			LPKEYUPCALLBACK Callback = *it;

			Callback( keyboardContext, _keyCode );
		}
	}

	void IWindow::onKeyDown( int _keyCode )
	{
		for ( vector<LPKEYDOWNCALLBACK>::iterator it = keyDownCallbacks.begin() ; it != keyDownCallbacks.end() ; ++it )
		{
			LPKEYDOWNCALLBACK Callback = *it;

			Callback( keyboardContext, _keyCode );
		}
	}

	void IWindow::onMouseUp()
	{
		for ( vector<LPMOUSEUPCALLBACK>::iterator it = mouseUpCallbacks.begin() ; it != mouseUpCallbacks.end() ; ++it )
		{
			LPMOUSEUPCALLBACK Callback = *it;

			Callback( keyboardContext, mouseContext, mouseX, mouseY );
		}
	}

	void IWindow::onMouseDown()
	{
		for ( vector<LPMOUSEDOWNCALLBACK>::iterator it = mouseDownCallbacks.begin() ; it != mouseDownCallbacks.end() ; ++it )
		{
			LPMOUSEDOWNCALLBACK Callback = *it;

			Callback( keyboardContext, mouseContext, mouseX, mouseY );
		}
	}

	void IWindow::onMouseMove()
	{
		for ( vector<LPMOUSEMOVECALLBACK>::iterator it = mouseMoveCallbacks.begin() ; it != mouseMoveCallbacks.end() ; ++it )
		{
			LPMOUSEMOVECALLBACK Callback = *it;

			Callback( keyboardContext, mouseContext, mouseX, mouseY );
		}
	}
}
