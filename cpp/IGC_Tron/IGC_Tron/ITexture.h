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

#ifndef _TEXTURE
#define _TEXTURE

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"
#include "Engine.h"
#include "IRenderer.h"

/***********************************************************************************/

namespace IGC
{

/***********************************************************************************/

	class ITexture
	{

/***********************************************************************************/
/** CONSTANTES                                                                    **/
/***********************************************************************************/

	public:

		static const int FORMAT_L8			= 0x01;
		static const int FORMAT_L8A8		= 0x02;
		static const int FORMAT_R8G8B8		= 0x03;
		static const int FORMAT_R8G8B8A8	= 0x04;

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	protected:

		Engine* engine;

		IRenderer* renderer;

		byte* data;

		int width;
		int height;

		int format;
		
		bool dirty;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie la classe sans allouer de mémoire pour la texture.
		*/
		ITexture( Engine* _engine );

		/*
			Libère les ressources.
		*/
		~ITexture();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers le moteur associé à cet objet.
		*/
		Engine* getEngine();

		/*
			Renvoie le renderer associé à cette texture.
		*/
		IRenderer* getRenderer();

		/*
			Renvoie la résolution horizontale de cette texture.
		*/
		int getWidth() { return width; };

		/*
			Renvoie la résolution verticale de cette texture.
		*/
		int getHeight() { return height; };

		/*
			Renvoie le format de cette texture.
		*/
		int getFormat() { return format; };

/***********************************************************************************/
/** METHODES PRIVEES                                                              **/
/***********************************************************************************/

	protected:

		int getPixelSize();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Génère une nouvelle texture de la résolution spécifiée.
		*/
		void create( int _width = 256, int _height = 256, int _format = FORMAT_R8G8B8A8 );

		/*
			Remplit cette texture d'une couleur unie définie par les paramètres.
		*/
		virtual void fill( float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 0.0f );
		virtual void fill( float _l = 0.0f, float _a = 0.0f );

		/*
			Charge un fichier au format Portable Network Graphics (*.png).
		*/
		void import( const char* _path );

		/*
			Force la mise à jour en mémoire vidéo.
		*/
		virtual void update() = 0;

		/*
			Active cette texture pour le prochain rendu.
		*/
		virtual void bind() = 0;

		/*
			Desactive la texture pour le prochain rendu.
		*/
		virtual void unbind() = 0;
	};
}

/***********************************************************************************/

#endif
