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

#ifndef _D3DMESH
#define _D3DMESH

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include <windows.h>

#include <d3dx9.h>
#include <dxerr.h>

#include "D3DRenderer.h"

#include "IMesh.h"

/***********************************************************************************/

namespace IGC
{
	class D3DMesh : public IMesh
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	private:

		DWORD dwFVF;

		LPDIRECT3DVERTEXDECLARATION9 lpVertexDeclaration;

		LPDIRECT3DVERTEXBUFFER9 lpVertexBuffer;
		LPDIRECT3DINDEXBUFFER9 lpIndexBuffer;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie la classe et alloue la m�moire vid�o pour les buffers.
		*/
		D3DMesh( Engine* _engine );

		/*
			Lib�re la m�moire vid�o r�serv�e pour les buffers.
		*/
		virtual ~D3DMesh();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Copie les donn�es de ce maillage en m�moire vid�o selon l'API utilis�e.
		*/
		virtual void update();

		/*
			Affiche ce maillage � l'�cran en fonction de la configuration de renderer sp�cifi�e.
		*/
		virtual void render();

	};
}

/***********************************************************************************/

#endif

#endif
