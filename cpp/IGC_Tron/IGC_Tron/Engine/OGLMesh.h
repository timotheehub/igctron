
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
			Instancie la classe et alloue la m�moire vid�o pour les buffers.
		*/
		OGLMesh( OGLRenderer* _renderer );

		/*
		~OGLMesh()
			Lib�re la m�moire vid�o r�serv�e pour les buffers.
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
