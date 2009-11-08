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

// TODO : appeler les callbacks stock?es dans closeCallbacks, keyUpCallbacks, ...

#ifndef _WIN32

#ifndef _X11WINDOW
#define _X11WINDOW

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include "IWindow.h"

#ifdef _WIN32
	#include <glew.h>
#else
	#include <GL/glew.h>
#endif
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>

/***********************************************************************************/

namespace IGC
{
	class Engine;

	class X11Window : public IWindow
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	private:

		Display* dpy;

		::Window win;

		int screen;

		XVisualInfo* vi;

		XF86VidModeModeInfo desk_mode;

		Bool doubleBuffered;

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
		X11Window( Engine* _engine );

		/*
			Lib?re les ressources internes.
		*/
		virtual ~X11Window();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers la structure Display associ?e ? cette fen?tre.
		*/
		Display* getDisplay() { return dpy; }

		/*
			Renvoie un pointeur vers la structure IWindow associ?e ? cette fen?tre.
		*/
		::Window getWindow() { return win; }

		/*
			Renvoie un pointeur vers la structure XVisualInfo associ?e ? cette fen?tre.
		*/
		XVisualInfo* getVisualInfo() { return vi; }

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Cr?e la fen?tre si n?cessaire puis l'affiche.
		*/
		virtual void show();

		/*
			Cache la fen?tre.
		*/
		virtual void hide();

		/*
			Met ? jour les dimensions de la fen?tre.
		*/
		void updateGeometry();
		
		/*
			Copie le back buffer dans le frame buffer.
		*/
		void swapBuffers();

	};
}

/***********************************************************************************/

#endif

#endif
