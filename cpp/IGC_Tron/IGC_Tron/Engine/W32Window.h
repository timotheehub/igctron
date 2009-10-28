
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

	protected:

		virtual void create( bool fullscreen = false );
		virtual void destroy();

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
		W32Window( Engine* _engine )
			Instancie la classe et initialise les ressources internes.
		*/
		W32Window( Engine* _engine );

		/*
		~W32Window()
			Lib�re les ressources internes.
		*/
		virtual ~W32Window();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
		getHandle()
			Renvoie le handle associ� � cette fen�tre.
		*/
		HWND getHandle() { return hWnd; }

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
		show()
			Cr�e la fen�tre si n�cessaire puis l'affiche.
		*/
		virtual void show();

		/*
		hide()
			Cache la fen�tre.
		*/
		virtual void hide();

	};
}

/***********************************************************************************/

#endif

#endif
