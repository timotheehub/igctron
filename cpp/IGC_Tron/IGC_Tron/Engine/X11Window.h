
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
			Libère les ressources internes.
		*/
		virtual ~X11Window();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
		getDisplay()
			Renvoie un pointeur vers la structure Display associée à cette fenêtre.
		*/
		Display* getDisplay() { return dpy; }

		/*
		getWindow()
			Renvoie un pointeur vers la structure IWindow associée à cette fenêtre.
		*/
		IWindow getWindow() { return win; }

		/*
		getVisualInfo()
			Renvoie un pointeur vers la structure XVisualInfo associée à cette fenêtre.
		*/
		XVisualInfo* getVisualInfo() { return vi; }

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
		show()
			Crée la fenêtre si nécessaire puis l'affiche.
		*/
		virtual void show();

		/*
		hide()
			Cache la fenêtre.
		*/
		virtual void hide();

		/*
		updateGeometry()
			Met à jour les dimensions de la fenêtre.
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
