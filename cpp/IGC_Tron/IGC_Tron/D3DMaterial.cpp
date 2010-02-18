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

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Engine.h"
#include "W32Window.h"
#include "D3DMaterial.h"

/***********************************************************************************/
/** DEBUG                                                                         **/
/***********************************************************************************/

#include "Debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***********************************************************************************/

namespace IGC
{

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	D3DMaterial::D3DMaterial( Engine* _engine ) : IMaterial( _engine )
	{
		lpMaterial = NULL;
	}

	D3DMaterial::~D3DMaterial()
	{
		if ( lpMaterial )
			delete lpMaterial;
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void D3DMaterial::update()
	{
		if ( lpMaterial )
			delete lpMaterial;

		lpMaterial = new D3DMATERIAL9;

		lpMaterial->Diffuse.r = diffuse.x;
		lpMaterial->Diffuse.g = diffuse.y;
		lpMaterial->Diffuse.b = diffuse.z;
		lpMaterial->Diffuse.a = diffuse.w;
		lpMaterial->Ambient.r = ambient.x;
		lpMaterial->Ambient.g = ambient.y;
		lpMaterial->Ambient.b = ambient.z;
		lpMaterial->Ambient.a = ambient.w;
		lpMaterial->Specular.r = specular.x;
		lpMaterial->Specular.g = specular.y;
		lpMaterial->Specular.b = specular.z;
		lpMaterial->Specular.a = specular.w;
		lpMaterial->Emissive.r = emissive.x;
		lpMaterial->Emissive.g = emissive.y;
		lpMaterial->Emissive.b = emissive.z;
		lpMaterial->Emissive.a = emissive.w;
		lpMaterial->Power = power;

		dirty = false;
	}

	void D3DMaterial::bind()
	{
		if ( dirty ) update();

		LPDIRECT3DDEVICE9 lpD3DDevice = ((D3DRenderer*)renderer)->getDevice();

		lpD3DDevice->SetMaterial( lpMaterial );

		lpD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	}

	void D3DMaterial::unbind()
	{
		LPDIRECT3DDEVICE9 lpD3DDevice = ((D3DRenderer*)renderer)->getDevice();

		lpD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	}

}

#endif
