
#ifdef _WIN32

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "OGLMesh.h"

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

	OGLMesh::OGLMesh( OGLRenderer* _renderer ) : IMesh( _renderer )
	{
		renderer = _renderer;
	}

	OGLMesh::~OGLMesh()
	{
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void OGLMesh::update()
	{
		// TODO : créer le VBO
	}

	void OGLMesh::render()
	{
		// TODO : rendre le VBO

		glDisable( GL_TEXTURE_2D ); // TEMP
		glColor3f( 0.0f, 0.0f, 0.0f );  // TEMP

		glBegin( GL_TRIANGLES );

		for ( uint k = 0 ; k < faceCount ; k++ )
		{
			uint3 face = faces[k];

			float3 a = vertices[face.x];
			float3 b = vertices[face.y];
			float3 c = vertices[face.z];

			glVertex3f( a.x, a.y, a.z );
			glVertex3f( b.x, b.y, b.z );
			glVertex3f( c.x, c.y, c.z );
		}

		glEnd();
	}

}

#endif
