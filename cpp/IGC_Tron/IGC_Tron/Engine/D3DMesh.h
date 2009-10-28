
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
			Instancie la classe et alloue la m�moire vid�o pour les buffers.
		*/
		D3DMesh( D3DRenderer* _renderer );

		/*
		~D3DMesh()
			Lib�re la m�moire vid�o r�serv�e pour les buffers.
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
			Copie les donn�es de ce maillage en m�moire vid�o selon l'API utilis�e.
		*/
		virtual void update();

		/*
		render()
			Affiche ce maillage � l'�cran en fonction de la configuration de renderer sp�cifi�e.
		*/
		virtual void render();

	};
}

/***********************************************************************************/

#endif

#endif
