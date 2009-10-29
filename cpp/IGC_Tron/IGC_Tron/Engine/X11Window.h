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

// TODO : appeler les callbacks stockées dans closeCallbacks, keyUpCallbacks, ...

#ifndef _WIN32

#ifndef _X11WINDOW
#define _X11WINDOW

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include "IWindow.h"

#include <GL/glx.h>
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

		IWindow win;

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
			Libère les ressources internes.
		*/
		virtual ~X11Window();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers la structure Display associée à cette fenêtre.
		*/
		Display* getDisplay() { return dpy; }

		/*
			Renvoie un pointeur vers la structure IWindow associée à cette fenêtre.
		*/
		IWindow getWindow() { return win; }

		/*
			Renvoie un pointeur vers la structure XVisualInfo associée à cette fenêtre.
		*/
		XVisualInfo* getVisualInfo() { return vi; }

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Crée la fenêtre si nécessaire puis l'affiche.
		*/
		virtual void show();

		/*
			Cache la fenêtre.
		*/
		virtual void hide();

		/*
			Met à jour les dimensions de la fenêtre.
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
