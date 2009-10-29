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

#ifndef _WINDOW
#define _WINDOW

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include <vector>

using namespace std;

/***********************************************************************************/

namespace IGC
{
	class Engine;

	class IWindow
	{

/***********************************************************************************/
/** TYPES                                                                         **/
/***********************************************************************************/

	public:

		typedef void ( *LPCLOSECALLBACK ) ( );

		typedef void ( *LPKEYUPCALLBACK ) ( int _keyboardContext, int _keyCode );
		typedef void ( *LPKEYDOWNCALLBACK ) ( int _keyboardContext, int _keyCode );

		typedef void ( *LPMOUSEMOVECALLBACK ) ( int _keyboardContext, int _mouseContext, int _mouseX, int _mouseY ) ;
		typedef void ( *LPMOUSEUPCALLBACK ) ( int _keyboardContext, int _mouseContext, int _mouseX, int _mouseY ) ;
		typedef void ( *LPMOUSEDOWNCALLBACK ) ( int _keyboardContext, int _mouseContext, int _mouseX, int _mouseY ) ;

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	protected:

		Engine* engine;

		vector<LPCLOSECALLBACK> closeCallbacks;

		vector<LPKEYUPCALLBACK> keyUpCallbacks;
		vector<LPKEYDOWNCALLBACK> keyDownCallbacks;

		vector<LPMOUSEMOVECALLBACK> mouseMoveCallbacks;
		vector<LPMOUSEUPCALLBACK> mouseUpCallbacks;
		vector<LPMOUSEDOWNCALLBACK> mouseDownCallbacks;

		int keyboardContext;
		int mouseContext;

		int mouseX;
		int mouseY;

		bool visible;
		bool active;

		int left;
		int top;
		int width;
		int height;

		int innerWidth;
		int innerHeight;

		bool fullscreen;

		char* title;

/***********************************************************************************/
/** METHODES PRIVEES                                                              **/
/***********************************************************************************/

	protected:

		virtual void create( bool fullscreen ) = 0;
		virtual void destroy() = 0;

/***********************************************************************************/
/** EVENEMENTS                                                                    **/
/***********************************************************************************/

	protected:

		void onClose();

		void onKeyUp( int _keyCode );
		void onKeyDown( int _keyCode );

		void onMouseMove();
		void onMouseUp();
		void onMouseDown();

/***********************************************************************************/
/** CONSTANTES                                                                    **/
/***********************************************************************************/

	public:

		static const int KC_NONE = 0x0;
		static const int KC_SHIFT = 0x1;	// bit à 1 si la touche shift du clavier est enfoncée
		static const int KC_CTRL = 0x2;		// bit à 1 si la touche ctrl du clavier est enfoncée
		static const int KC_ALT = 0x4;		// bit à 1 si la touche alt du clavier est enfoncée

		static const int MC_NONE = 0x0;
		static const int MC_LEFT = 0x1;		// bit à 1 si le bouton gauche de la souris est enfoncé
		static const int MC_RIGHT = 0x2;	// bit à 1 si le bouton droit de la souris est enfoncé
		static const int MC_MIDDLE = 0x4;	// bit à 1 si le bouton du milieu de la souris est enfoncé

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie la classe et initialise les ressources internes.
		*/
		IWindow( Engine* _engine );

		/*
			Libère les ressources internes.
		*/
		virtual ~IWindow();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers le moteur associé à cette fenêtre.
		*/
		Engine* getEngine();

		/*
			Spécifie le titre de la fenêtre.
		*/
		void setTitle( char* _title );

		/*
			Spécifie la position horizontale (en pixels) de la fenêtre à l'écran.
		*/
		void setLeft( int _value = 120 );

		/*
			Spécifie la position verticale (en pixels) de la fenêtre à l'écran.
		*/
		void setTop( int _value = 80 );

		/*
			Renvoie la position horizontale (en pixels) de la fenêtre à l'écran.
		*/
		int getLeft();

		/*
			Renvoie la position verticale (en pixels) de la fenêtre à l'écran.
		*/
		int getTop();

		/*
			Spécifie la taille horizontale (en pixels) de la fenêtre.
		*/
		void setWidth( int _value = 800 );

		/*
			Spécifie la taille verticale (en pixels) de la fenêtre.
		*/
		void setHeight( int _value = 600 );

		/*
			Renvoie la taille horizontale (en pixels) de la fenêtre.
		*/
		int getWidth();

		/*
			Renvoie la taille verticale (en pixels) de la fenêtre.
		*/
		int getHeight();

		/*
			Renvoie la taille horizontale (en pixels) du cadre interne de la fenêtre.
		*/
		int getInnerWidth();

		/*
			Renvoie la taille verticale (en pixels) du cadre interne de la fenêtre.
		*/
		int getInnerHeight();

		/*
			Renvoie true si la fenêtre est visible.
		*/
		bool isVisible();

		/*
			Renvoie true si la fenêtre est active (elle ne l'est plus dès lors que l'utilisateur
			clique sur la croix en haut à droite).
		*/
		bool isActive();

		/*
			Ajoute une callback devant être appelée lorsque la fenêtre est fermée.
		*/
		void registerCloseCallback ( LPCLOSECALLBACK _callback );

		/*
			Supprime une callback devant être appelée lorsque la fenêtre est fermée.
		*/
		void unregisterCloseCallback ( LPCLOSECALLBACK _callback );

		/*
			Ajoute une callback devant être appelée lorsqu'une touche du clavier est relachée.
		*/
		void registerKeyUpCallback ( LPKEYUPCALLBACK _callback );

		/*
			Supprime une callback devant être appelée lorsqu'une touche du clavier est relachée.
		*/
		void unregisterKeyUpCallback ( LPKEYUPCALLBACK _callback );

		/*
			Ajoute une callback devant être appelée lorsqu'une touche du clavier est enfoncée.
		*/
		void registerKeyDownCallback ( LPKEYDOWNCALLBACK _callback );

		/*
			Supprime une callback devant être appelée lorsqu'une touche du clavier est enfoncée.
		*/
		void unregisterKeyDownCallback ( LPKEYDOWNCALLBACK _callback );

		/*
			Ajoute une callback devant être appelée lorsque la souris est en mouvement.
		*/
		void registerMouseMoveCallback ( LPMOUSEMOVECALLBACK _callback );

		/*
			Supprime une callback devant être appelée lorsque la souris est en mouvement.
		*/
		void unregisterMouseMoveCallback ( LPMOUSEMOVECALLBACK _callback );

		/*
			Ajoute une callback devant être appelée lorsqu'un bouton de la souris est relaché.
		*/
		void registerMouseUpCallback ( LPMOUSEUPCALLBACK _callback );

		/*
			Supprime une callback devant être appelée lorsqu'un bouton de la souris est relaché.
		*/
		void unregisterMouseUpCallback ( LPMOUSEUPCALLBACK _callback );

		/*
			Ajoute une callback devant être appelée lorsqu'un bouton de la souris est enfoncé.
		*/
		void registerMouseDownCallback ( LPMOUSEDOWNCALLBACK _callback );

		/*
			Supprime une callback devant être appelée lorsqu'un bouton de la souris est enfoncé.
		*/
		void unregisterMouseDownCallback ( LPMOUSEDOWNCALLBACK _callback );

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Crée la fenêtre si nécessaire puis l'affiche.
		*/
		virtual void show() = 0;

		/*
			Cache la fenêtre.
		*/
		virtual void hide() = 0;

	};
}

/***********************************************************************************/

#endif
