
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
			Instancie la classe et alloue la m�moire vid�o pour une surface de rendu
			dont la taille correspond � celle de la fen�tre associ�e � _engine.
		*/
		OGLRenderer( Engine* _engine );

		/*
		~OGLRenderer()
			Lib�re la m�moire vid�o r�serv�e pour une surface de rendu.
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
			Lib�re toutes les ressources relatives � OpenGL.
		*/
		virtual void finalize();

		/*
		update()
			Met � jour l'affichage en copiant le contenu du back buffer vers le frame buffer.
		*/
		virtual void update();

		virtual void clear( float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _depth = 1.0f );

	};
}

/***********************************************************************************/

#endif
