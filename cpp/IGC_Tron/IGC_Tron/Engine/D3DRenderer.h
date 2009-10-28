
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
		D3DRenderer( Engine* _engine )
		Instancie la classe et alloue la mémoire vidéo pour une surface de rendu
		dont la taille correspond à celle de la fenêtre associée à _engine.
		*/
		D3DRenderer( Engine* _engine );

		/*
		~D3DRenderer()
		Libère la mémoire vidéo réservée pour une surface de rendu.
		*/
		virtual ~D3DRenderer();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

		/*
		getDevice()
			Renvoie le device associé à cette instance ou NULL si celui-ci n'a
			pas encore été créé.
		*/
		LPDIRECT3DDEVICE9 getDevice();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

		/*
		initialize()
			Initialise Direct3D et lui associe la surface de rendu.
		*/
		virtual void initialize();

		/*
		finalize()
			Libère toutes les ressources relatives à Direct3D.
		*/
		virtual void finalize();

		/*
		update()
			Met à jour l'affichage en copiant le contenu du back buffer vers le frame buffer.
		*/
		virtual void update();

		virtual void clear( float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _depth = 1.0f );

	};
}

/***********************************************************************************/

#endif

#endif
