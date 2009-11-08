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
		static const int KC_SHIFT = 0x1;	// bit ? 1 si la touche shift du clavier est enfonc?e
		static const int KC_CTRL = 0x2;		// bit ? 1 si la touche ctrl du clavier est enfonc?e
		static const int KC_ALT = 0x4;		// bit ? 1 si la touche alt du clavier est enfonc?e

		static const int MC_NONE = 0x0;
		static const int MC_LEFT = 0x1;		// bit ? 1 si le bouton gauche de la souris est enfonc?
		static const int MC_RIGHT = 0x2;	// bit ? 1 si le bouton droit de la souris est enfonc?
		static const int MC_MIDDLE = 0x4;	// bit ? 1 si le bouton du milieu de la souris est enfonc?

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie la classe et initialise les ressources internes.
		*/
		IWindow( Engine* _engine );

		/*
			Lib?re les ressources internes.
		*/
		virtual ~IWindow();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers le moteur associ? ? cette fen?tre.
		*/
		Engine* getEngine();

		/*
			Sp?cifie le titre de la fen?tre.
		*/
		void setTitle( const char* _title );

		/*
			Sp?cifie la position horizontale (en pixels) de la fen?tre ? l'?cran.
		*/
		void setLeft( int _value = 120 );

		/*
			Sp?cifie la position verticale (en pixels) de la fen?tre ? l'?cran.
		*/
		void setTop( int _value = 80 );

		/*
			Renvoie la position horizontale (en pixels) de la fen?tre ? l'?cran.
		*/
		int getLeft();

		/*
			Renvoie la position verticale (en pixels) de la fen?tre ? l'?cran.
		*/
		int getTop();

		/*
			Sp?cifie la taille horizontale (en pixels) de la fen?tre.
		*/
		void setWidth( int _value = 800 );

		/*
			Sp?cifie la taille verticale (en pixels) de la fen?tre.
		*/
		void setHeight( int _value = 600 );

		/*
			Renvoie la taille horizontale (en pixels) de la fen?tre.
		*/
		int getWidth();

		/*
			Renvoie la taille verticale (en pixels) de la fen?tre.
		*/
		int getHeight();

		/*
			Renvoie la taille horizontale (en pixels) du cadre interne de la fen?tre.
		*/
		int getInnerWidth();

		/*
			Renvoie la taille verticale (en pixels) du cadre interne de la fen?tre.
		*/
		int getInnerHeight();

		/*
			Renvoie true si la fen?tre est visible.
		*/
		bool isVisible();

		/*
			Renvoie true si la fen?tre est active (elle ne l'est plus d?s lors que l'utilisateur
			clique sur la croix en haut ? droite).
		*/
		bool isActive();

		/*
			Ajoute une callback devant ?tre appel?e lorsque la fen?tre est ferm?e.
		*/
		void registerCloseCallback ( LPCLOSECALLBACK _callback );

		/*
			Supprime une callback devant ?tre appel?e lorsque la fen?tre est ferm?e.
		*/
		void unregisterCloseCallback ( LPCLOSECALLBACK _callback );

		/*
			Ajoute une callback devant ?tre appel?e lorsqu'une touche du clavier est relach?e.
		*/
		void registerKeyUpCallback ( LPKEYUPCALLBACK _callback );

		/*
			Supprime une callback devant ?tre appel?e lorsqu'une touche du clavier est relach?e.
		*/
		void unregisterKeyUpCallback ( LPKEYUPCALLBACK _callback );

		/*
			Ajoute une callback devant ?tre appel?e lorsqu'une touche du clavier est enfonc?e.
		*/
		void registerKeyDownCallback ( LPKEYDOWNCALLBACK _callback );

		/*
			Supprime une callback devant ?tre appel?e lorsqu'une touche du clavier est enfonc?e.
		*/
		void unregisterKeyDownCallback ( LPKEYDOWNCALLBACK _callback );

		/*
			Ajoute une callback devant ?tre appel?e lorsque la souris est en mouvement.
		*/
		void registerMouseMoveCallback ( LPMOUSEMOVECALLBACK _callback );

		/*
			Supprime une callback devant ?tre appel?e lorsque la souris est en mouvement.
		*/
		void unregisterMouseMoveCallback ( LPMOUSEMOVECALLBACK _callback );

		/*
			Ajoute une callback devant ?tre appel?e lorsqu'un bouton de la souris est relach?.
		*/
		void registerMouseUpCallback ( LPMOUSEUPCALLBACK _callback );

		/*
			Supprime une callback devant ?tre appel?e lorsqu'un bouton de la souris est relach?.
		*/
		void unregisterMouseUpCallback ( LPMOUSEUPCALLBACK _callback );

		/*
			Ajoute une callback devant ?tre appel?e lorsqu'un bouton de la souris est enfonc?.
		*/
		void registerMouseDownCallback ( LPMOUSEDOWNCALLBACK _callback );

		/*
			Supprime une callback devant ?tre appel?e lorsqu'un bouton de la souris est enfonc?.
		*/
		void unregisterMouseDownCallback ( LPMOUSEDOWNCALLBACK _callback );

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Cr?e la fen?tre si n?cessaire puis l'affiche.
		*/
		virtual void show() = 0;

		/*
			Cache la fen?tre.
		*/
		virtual void hide() = 0;

	};
}

/***********************************************************************************/

#endif
