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
			Instancie la classe et alloue la mémoire vidéo pour une surface de rendu dont la taille
			correspond à celle de la fenêtre associée à _engine.
		*/
		OGLRenderer( Engine* _engine );

		/*
			Libère la mémoire vidéo réservée pour une surface de rendu.
		*/
		virtual ~OGLRenderer();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	private:

		/*
			Spécifie une police pour le prochain rendu de texte.
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
			Libère toutes les ressources relatives à OpenGL.
		*/
		virtual void finalize();

		/*
			Met à jour l'affichage en copiant le contenu du back buffer vers le frame buffer.
		*/
		virtual void update();

		/*
			Remplit le back buffer de la couleur spécifiée et le depth buffer de la profondeur spécifiée.
		*/
		virtual void clear( float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _depth = 1.0f );

		/*
			Affiche du texte à la position absolue spécifiée avec la couleur spécifiée en fonction de la police
			qui aura précédemment été définie.
		*/
		virtual void drawText( char* _text, int _x, int _y, float _r, float _g, float _b, float _a );

	};
}

/***********************************************************************************/

#endif
