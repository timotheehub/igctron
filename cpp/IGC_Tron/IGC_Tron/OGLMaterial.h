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

#ifndef _OGLMATERIAL
#define _OGLMATERIAL

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include "OGLRenderer.h"

#include "IMaterial.h"

/***********************************************************************************/

namespace IGC
{
	class OGLMaterial : public IMaterial
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
		OGLMaterial( Engine* _engine );

		/*
			Libère les ressources en mémoire vidéo.
		*/
		~OGLMaterial();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Force la génération des ressources OpenGL pour cette Material.
		*/
		virtual void update();

		/*
			Active cette Material pour le prochain rendu.
		*/
		virtual void bind();

		/*
			Desactive la Material pour le prochain rendu.
		*/
		virtual void unbind();
	};
}

/***********************************************************************************/

#endif
