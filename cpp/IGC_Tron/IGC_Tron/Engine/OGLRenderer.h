
#ifndef _OGLRENDERER
#define _OGLRENDERER

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include "IRenderer.h"

#include <GL/glew.h>
#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glu.h>			// Header File For The GLu32 Library

#ifndef _WIN32
	#include <GL/glx.h>
	#include <X11/extensions/xf86vmode.h>
	#include <X11/keysym.h>
#endif

/***********************************************************************************/

namespace IGC
{
	class Engine;

	class OGLRenderer : public IRenderer
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	private:

		#ifdef _WIN32
			HDC hDC;
			HGLRC hRC;
		#else
			GLXContext ctx;
		#endif

		GLuint glRenderTexture;

		void* glHostTextureData;

		GLuint glFontList;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
		OGLRenderer( Engine* _engine )
			Instancie la classe et alloue la mémoire vidéo pour une surface de rendu
			dont la taille correspond à celle de la fenêtre associée à _engine.
		*/
		OGLRenderer( Engine* _engine );

		/*
		~OGLRenderer()
			Libère la mémoire vidéo réservée pour une surface de rendu.
		*/
		virtual ~OGLRenderer();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

		/*
		initialize()
			Initialise OpenGL et lui associe la surface de rendu.
		*/
		virtual void initialize();

		/*
		finalize()
			Libère toutes les ressources relatives à OpenGL.
		*/
		virtual void finalize();

		/*
		update()
			Met à jour l'affichage en copiant le contenu du back buffer vers le frame buffer.
		*/
		virtual void update();

		virtual void clear( float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _depth = 1.0f );

	};
}

/***********************************************************************************/

#endif
