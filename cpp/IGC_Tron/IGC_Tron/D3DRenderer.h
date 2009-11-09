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

#ifndef _D3DRENDERER
#define _D3DRENDERER

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include <windows.h>

#include <d3dx9.h>
#include <dxerr.h>

#include "IRenderer.h"

/***********************************************************************************/

namespace IGC
{
	class Engine;

	class D3DRenderer : public IRenderer
	{

/***********************************************************************************/
/** CLASSES AMIES                                                                 **/
/***********************************************************************************/

		friend class D3DCamera;
		friend class D3DFont;
		friend class D3DMesh;
		friend class D3DModel;

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	private:

		LPDIRECT3D9 lpD3D;
		LPDIRECT3DDEVICE9 lpD3DDevice;

		LPDIRECT3DTEXTURE9 lpRenderTexture;

		LPDIRECT3DPIXELSHADER9 lpPixelShader;
		LPDIRECT3DVERTEXSHADER9 lpVertexShader;

		LPDIRECT3DVERTEXDECLARATION9 lpVertexDeclaration;

		LPDIRECT3DVERTEXBUFFER9 lpVertexBuffer;
		LPDIRECT3DINDEXBUFFER9 lpIndexBuffer;

		LPD3DXFONT lpFont;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie la classe et alloue la mémoire vidéo pour une surface de rendu dont la taille
			correspond à celle de la fenêtre associée à _engine.
		*/
		D3DRenderer( Engine* _engine );

		/*
			Libère la mémoire vidéo réservée pour une surface de rendu.
		*/
		virtual ~D3DRenderer();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie le device associé à cette instance ou NULL si celui-ci n'a pas encore été créé.
		*/
		LPDIRECT3DDEVICE9 getDevice();

	private:

		/*
			Spécifie une police pour le prochain rendu de texte.
		*/
		void setFont( LPD3DXFONT _lpFont );

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Initialise Direct3D et lui associe la surface de rendu.
		*/
		virtual void initialize();

		/*
			Libère toutes les ressources relatives ? Direct3D.
		*/
		virtual void finalize();

		/*
			Met à jour l'affichage en copiant le contenu du back buffer vers le frame buffer.
		*/
		virtual void update();

		/*
			Active ou non la transparence pour le prochain rendu.
		*/
		virtual void setTransparency( bool _value );

		/*
			Remplit le back buffer de la couleur spécifiée et le depth buffer de la profondeur spécifiée.
		*/
		virtual void clear( float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _depth = 1.0f );

		/*
			Affiche du texte à la position absolue spécifiée avec la couleur spécifiée en fonction de la police
			qui aura précédemment été définie.
		*/
		virtual void drawText( const char* _text, int _x, int _y, float _r, float _g, float _b, float _a );

		/*
			Affiche une image à la position absolue spécifiée avec la couleur spécifiée en fonction de la texture
			qui aura précédemment été définie.
		*/
		virtual void drawImage( int _x0, int _y0, int _x1, int _y1,
									float _px = 0.0f, float _py = 0.0f, float _sx = 1.0f, float _sy = 1.0f,
											float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f );

	};
}

/***********************************************************************************/

#endif

#endif
