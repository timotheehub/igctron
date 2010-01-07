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

#ifndef _OGLTEXTURE
#define _OGLTEXTURE

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include "OGLRenderer.h"

#include "ITexture.h"

/***********************************************************************************/

namespace IGC
{
	class OGLTexture : public ITexture
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	private:

		GLuint glTexID;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie la classe et alloue la mémoire pour les ressources OpenGL.
		*/
		OGLTexture( Engine* _engine );

		/*
			Libère les ressources en mémoire vidéo.
		*/
		~OGLTexture();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Force la génération des ressources OpenGL pour cette texture.
		*/
		virtual void update();

		/*
			Active cette texture pour le prochain rendu.
		*/
		virtual void bind();

		/*
			Desactive la texture pour le prochain rendu.
		*/
		virtual void unbind();
	};
}

/***********************************************************************************/

#endif
