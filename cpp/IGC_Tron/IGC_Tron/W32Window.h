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

#ifndef _W32WINDOW
#define _W32WINDOW

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include <windows.h>

#include "IWindow.h"

/***********************************************************************************/

namespace IGC
{
	class Engine;

	class W32Window : public IWindow
	{

/***********************************************************************************/
/** FONCTIONS AMIES                                                               **/
/***********************************************************************************/

	public:

		friend LRESULT WINAPI windowCallback( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

		friend DWORD WINAPI windowThread( LPVOID args );

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	private:

		WNDCLASSEX wc; // informations sur la fen�tre
		HWND hWnd; // identifiant de la fen�tre

		HANDLE thread;
		HANDLE emptyEvent;
		HANDLE synchronizer;

		bool ready;

/***********************************************************************************/
/** METHODES PRIVEES                                                              **/
/***********************************************************************************/

	private:

		virtual void create( bool fullscreen = false );
		virtual void destroy();

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie la classe et initialise les ressources internes.
		*/
		W32Window( Engine* _engine );

		/*
			Lib�re les ressources internes.
		*/
		virtual ~W32Window();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie le handle associ� � cette fen�tre.
		*/
		HWND getHandle() { return hWnd; }

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Cr�e la fen�tre si n�cessaire puis l'affiche.
		*/
		virtual void show();

		/*
			Cache la fen�tre.
		*/
		virtual void hide();

	};
}

/***********************************************************************************/

#endif

#endif
