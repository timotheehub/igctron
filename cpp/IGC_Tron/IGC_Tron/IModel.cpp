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

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include <math.h>

#include "lib3ds/lib3ds.h"

#include "Common.h"
#include "Factory.h"
#include "IModel.h"
#include "D3DModel.h"
#include "OGLModel.h"

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

	IModel::IModel( Engine* _engine )
	{
		engine = _engine;

		renderer = engine->getRenderer();

		parent = NULL;

		center.x = 0.0f;
		center.y = 0.0f;
		center.z = 0.0f;

		angle.x = 0.0f;
		angle.y = 0.0f;
		angle.z = 0.0f;

		size.x = 1.0f;
		size.y = 1.0f;
		size.z = 1.0f;

		dirty = true;

		mesh = NULL;
	}

	IModel::~IModel()
	{
		if ( mesh )
			engine->getFactory()->release( (Mesh*)mesh );

		for ( vector<IModel*>::iterator it = children.begin() ; it != children.end() ; ++it )
		{
			engine->getFactory()->release( (Model*)*it );
		}
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	Engine* IModel::getEngine()
	{
		return engine;
	}

	IRenderer* IModel::getRenderer()
	{
		return renderer;
	}

	IMesh* IModel::newMesh()
	{
		if ( mesh )
			engine->getFactory()->release( (Mesh*)mesh );

		mesh = (IMesh*)engine->getFactory()->acquire( (Mesh*)NULL );

		return mesh;
	}

	IMesh* IModel::getMesh()
	{
		return mesh;
	}

	void IModel::setMesh( IMesh* _mesh )
	{
		if ( mesh )
			engine->getFactory()->release( (Mesh*)mesh );

		mesh = _mesh;

		if ( mesh )
			engine->getFactory()->acquire( (Mesh*)mesh );
	}

	IModel* IModel::newChild()
	{
		IModel* child = engine->getFactory()->acquire( (Model*)NULL );

		child->parent = this;

		children.push_back( child );

		return child;
	}

	void IModel::addChild( IModel* _child )
	{
		engine->getFactory()->acquire( (Model*)_child );

		_child->parent = this;

		children.push_back( _child );
	}

	IModel* IModel::getChild( int _id )
	{
		return children[_id];
	}

	int IModel::getChildCount()
	{
		return children.size();
	}

	void IModel::delChild( IModel* _child )
	{
		for ( vector<IModel*>::iterator it = children.begin() ; it != children.end() ; ++it )
		{
			if ( *it == _child )
			{
				children.erase( it );

				_child->parent = NULL;

				engine->getFactory()->release( (Model*)_child );
			}
		}
	}

	void IModel::setCenter( float _x, float _y, float _z )
	{
		center = make_float3( _x, _y, _z );

		dirty = true;
	}

	void IModel::setCenter( float3& _center )
	{
		center = _center;

		dirty = true;
	}

	void IModel::setAngle( float _x, float _y, float _z )
	{
		angle = make_float3( _x, _y, _z );

		dirty = true;
	}

	void IModel::setAngle( float3& _angle )
	{
		angle = _angle;

		dirty = true;
	}

	void IModel::setSize( float _x, float _y, float _z )
	{
		size = make_float3( _x, _y, _z );

		dirty = true;
	}

	void IModel::setSize( float3& _size )
	{
		size = _size;

		dirty = true;
	}

	void IModel::move( float _x, float _y, float _z )
	{
		center.x += _x;
		center.y += _y;
		center.z += _z;

		dirty = true;
	}

	void IModel::rotate( float _x, float _y, float _z )
	{
		angle.x -= _x;
		angle.y -= _y;
		angle.z -= _z;

		dirty = true;
	}

	void IModel::grow( float _x, float _y, float _z )
	{
		size.x *= _x;
		size.y *= _y;
		size.z *= _z;

		dirty = true;
	}

	void IModel::shrink( float _x, float _y, float _z )
	{
		size.x /= _x;
		size.y /= _y;
		size.z /= _z;

		dirty = true;
	}

	float4x4 IModel::getWorldMatrix()
	{
		if ( dirty ) update();

		return matWorld;
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void IModel::update()
	{
		matrixTranslation( matCenter, center.x, center.y, center.z );
		matrixRotationYawPitchRoll( matAngle, angle.y, angle.x, angle.z );
		matrixScale( matSize, size.x, size.y, size.z );

		matWorld = matSize * matAngle * matCenter;

		if ( parent )
			matWorld = matWorld * parent->getWorldMatrix();

		dirty = false;
	}

	void IModel::render()
	{
		for ( vector<IModel*>::iterator it = children.begin() ; it != children.end() ; ++it )
		{
			(*it)->render();
		}
	}

	static void import_mesh( IModel* model, Lib3dsFile* file, Lib3dsMeshInstanceNode* node )
	{
		Lib3dsMesh* mesh3ds = lib3ds_file_mesh_for_node( file, (Lib3dsNode*)node );

		if ( mesh3ds == NULL || mesh3ds->vertices == 0 ) return;

		// d?compte du nombre de mat?riaux
		{
			int materials[255];

			int index = -1;
			int count = 0;

			for ( int j, i = 0 ; i < mesh3ds->nfaces ; ++i )
			{
				if ( index != mesh3ds->faces[i].material )
				{
					index = mesh3ds->faces[i].material;

					for ( j = 0 ; j < count ; j++ )
					{
						if ( index == materials[j] ) break;
					}

					if ( j == count ) materials[count++] = index;
				}
			}

			if ( count > 1 )
			{
				// TODO : scinder le mod?le en plusieurs autres, un par mat?riau
			}
		}

		// cr?ation du maillage pour ce mod?le 3d

		IMesh* mesh = model->newMesh();

		// d?finition des propri?t?s du maillage

		mesh->hasVertices = true;
		mesh->hasNormals = (mesh3ds->faces != 0);
		mesh->hasColors = true;
		mesh->hasTexcoords = (mesh3ds->texcos != 0);

		// allocation de la m?moire

		mesh->setVertexCount( mesh3ds->nvertices );
		mesh->setFaceCount( mesh3ds->nfaces );

		// copie des donn?es

		{
			float (*vertices3ds)[3] = mesh3ds->vertices;

			for ( int i = 0 ; i < mesh3ds->nvertices ; ++i )
				mesh->setVertex( i, vertices3ds[i] );
		}

		if ( mesh->hasNormals )
		{
			float (*normals3ds)[3] = (float(*)[3])malloc(sizeof(float) * 9 * mesh3ds->nfaces);

			lib3ds_mesh_calculate_vertex_normals( mesh3ds, normals3ds );

			for ( int i = 0 ; i < mesh3ds->nvertices ; ++i )
				mesh->setNormal( i, normals3ds[i] );

			free( normals3ds );
		}

		if ( mesh->hasTexcoords )
		{
			float (*texcoords3ds)[2] = mesh3ds->texcos;

			for ( int i = 0 ; i < mesh3ds->nvertices ; ++i )
				mesh->setTexcoord( i, texcoords3ds[i] );
		}

		{
			for ( int i = 0 ; i < mesh3ds->nvertices ; ++i )
				mesh->setColor( i, 1.0f, 1.0f, 1.0f, 1.0f );
		}

		{
			for ( int i = 0 ; i < mesh3ds->nfaces ; ++i )
			{
				ushort* face = mesh3ds->faces[i].index;

				mesh->setFace( i, face[0], face[1], face[2] );
			}
		}

		// synchro des donn?es en m?moire vid?o

		mesh->update();
	}

	static void import_nodes( IModel* model, Lib3dsFile* file, Lib3dsNode* root )
	{
		for ( Lib3dsNode* node = root ; node ; node = node->next )
		{
			if ( node->type == LIB3DS_NODE_MESH_INSTANCE )
			{
				IModel* child = model->newChild();

				import_mesh( child, file, (Lib3dsMeshInstanceNode*)node );

				import_nodes( child, file, node->childs );
			}
		}
	}

	void IModel::import( const char* _path )
	{
		Lib3dsFile* file;

		file = lib3ds_file_open( _path );

		_assert( file != NULL, __FILE__, __LINE__, "IModel::import() : Unable to access file." );

		// TODO : spawner des instances de Material
		{
			for ( int i = 0 ; i < file->nmaterials ; ++i )
			{
				Lib3dsMaterial* mtl = file->materials[i];

				printf( "newmtl %s\n", mtl->name );
				printf( "Ka %f %f %f\n", mtl->ambient[0], mtl->ambient[1], mtl->ambient[2] );
				printf( "Kd %f %f %f\n", mtl->diffuse[0], mtl->diffuse[1], mtl->diffuse[2] );
				printf( "Ks %f %f %f\n", mtl->specular[0], mtl->specular[1], mtl->specular[2] );
				printf( "illum 2\n" );
				printf( "Ns %f\n", pow(2, 10 * mtl->shininess + 1) );
				printf( "d %f\n", 1.0 - mtl->transparency );
				printf( "map_Kd %s\n", mtl->texture1_map.name );
				printf( "map_bump %s\n", mtl->bump_map.name );
				printf( "map_d %s\n", mtl->opacity_map.name );
				printf( "refl %s\n", mtl->reflection_map.name );
				printf( "map_KS %s\n", mtl->specular_map.name );
				printf( "\n" );
			}
		}

		if ( file->nodes == NULL ) lib3ds_file_create_nodes_for_meshes( file );

		lib3ds_file_eval( file, 0 );

		import_nodes( this, file, file->nodes );

		lib3ds_file_free( file );
	}
}
