
#ifndef _OGLMESH
#define _OGLMESH

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include "OGLRenderer.h"

#include "IMesh.h"

/***********************************************************************************/

namespace IGC
{
	class OGLMesh : public IMesh
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	private:

		OGLRenderer* renderer;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
		OGLMesh( OGLRenderer* _renderer )
			Instancie la classe et alloue la mémoire vidéo pour les buffers.
		*/
		OGLMesh( OGLRenderer* _renderer );

		/*
		~OGLMesh()
			Libère la mémoire vidéo réservée pour les buffers.
		*/
		virtual ~OGLMesh();

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
