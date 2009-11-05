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

#ifndef _OGLRENDERER
#define _OGLRENDERER

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include "IRenderer.h"

#ifdef _WIN32
	#include <glew.h>
#else
	#include <GL/glew.h>
#endif
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
/** CLASSES AMIES                                                                 **/
/***********************************************************************************/

		friend class OGLCamera;
		friend class OGLFont;
		friend class OGLMesh;
		friend class OGLModel;

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
			Instancie la classe et alloue la m�moire vid�o pour une surface de rendu dont la taille
			correspond � celle de la fen�tre associ�e � _engine.
		*/
		OGLRenderer( Engine* _engine );

		/*
			Lib�re la m�moire vid�o r�serv�e pour une surface de rendu.
		*/
		virtual ~OGLRenderer();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	private:

		/*
			Sp�cifie une police pour le prochain rendu de texte.
		*/
		void setFont( GLuint _glFontList );

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Initialise OpenGL et lui associe la surface de rendu.
		*/
		virtual void initialize();

		/*
			Lib�re toutes les ressources relatives � OpenGL.
		*/
		virtual void finalize();

		/*
			Met � jour l'affichage en copiant le contenu du back buffer vers le frame buffer.
		*/
		virtual void update();

		/*
			Remplit le back buffer de la couleur sp�cifi�e et le depth buffer de la profondeur sp�cifi�e.
		*/
		virtual void clear( float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _depth = 1.0f );

		/*
			Affiche du texte � la position absolue sp�cifi�e avec la couleur sp�cifi�e en fonction de la police
			qui aura pr�c�demment �t� d�finie.
		*/
		virtual void drawText( const char* _text, int _x, int _y, float _r, float _g, float _b, float _a );

	};
}

/***********************************************************************************/

#endif
