
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

		D3DRenderer* renderer;

		DWORD dwFVF;

		LPDIRECT3DVERTEXDECLARATION9 lpVertexDeclaration;

		LPDIRECT3DVERTEXBUFFER9 lpVertexBuffer;
		LPDIRECT3DINDEXBUFFER9 lpIndexBuffer;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
		D3DMesh( D3DRenderer* _renderer )
			Instancie la classe et alloue la mémoire vidéo pour les buffers.
		*/
		D3DMesh( D3DRenderer* _renderer );

		/*
		~D3DMesh()
			Libère la mémoire vidéo réservée pour les buffers.
		*/
		virtual ~D3DMesh();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

		/*
		update()
			Copie les données de ce maillage en mémoire vidéo selon l'API utilisée.
		*/
		virtual void update();

		/*
		render()
			Affiche ce maillage à l'écran en fonction de la configuration de renderer spécifiée.
		*/
		virtual void render();

	};
}

/***********************************************************************************/

#endif

#endif
