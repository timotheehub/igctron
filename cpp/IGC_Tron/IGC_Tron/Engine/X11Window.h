
// TODO : appeler les callbacks stock�es dans closeCallbacks, keyUpCallbacks, ...

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

	protected:

		virtual void create( bool fullscreen = false );
		virtual void destroy();

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
		X11Window( Engine* _engine )
			Instancie la classe et initialise les ressources internes.
		*/
		X11Window( Engine* _engine );

		/*
		~X11Window()
			Lib�re les ressources internes.
		*/
		virtual ~X11Window();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
		getDisplay()
			Renvoie un pointeur vers la structure Display associ�e � cette fen�tre.
		*/
		Display* getDisplay() { return dpy; }

		/*
		getWindow()
			Renvoie un pointeur vers la structure IWindow associ�e � cette fen�tre.
		*/
		IWindow getWindow() { return win; }

		/*
		getVisualInfo()
			Renvoie un pointeur vers la structure XVisualInfo associ�e � cette fen�tre.
		*/
		XVisualInfo* getVisualInfo() { return vi; }

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

		/*
		updateGeometry()
			Met � jour les dimensions de la fen�tre.
		*/
		void updateGeometry();
		
		/*
		swapBuffers()
			Copie le back buffer dans le frame buffer.
		*/
		void swapBuffers();

	};
}

/***********************************************************************************/

#endif

#endif
