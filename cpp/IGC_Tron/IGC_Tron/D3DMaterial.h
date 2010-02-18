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

#ifdef _WIN32

#ifndef _D3DMATERIAL
#define _D3DMATERIAL

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include <windows.h>

#include <d3dx9.h>
#include <dxerr.h>

#include "D3DRenderer.h"

#include "IMaterial.h"

/***********************************************************************************/

namespace IGC
{
	class D3DMaterial : public IMaterial
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	private:

		D3DMATERIAL9* lpMaterial;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie la classe et alloue la mémoire pour les ressources Direct3D.
		*/
		D3DMaterial( Engine* _engine );

		/*
			Libère les ressources en mémoire vidéo.
		*/
		~D3DMaterial();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Force la génération des ressources Direct3D pour ce matériau.
		*/
		virtual void update();

		/*
			Active ce matériau pour le prochain rendu.
		*/
		virtual void bind();

		/*
			Desactive le matériau pour le prochain rendu.
		*/
		virtual void unbind();

	};
}

/***********************************************************************************/

#endif

#endif
