
/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include <math.h>

#include "IModel.h"
#include "Common.h"

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

	IModel::IModel( IRenderer* _renderer )
	{
		renderer = _renderer;

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
		for ( vector<IModel*>::iterator it = children.begin() ; it != children.end() ; ++it )
		{
			delete *it;
		}
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	IMesh* IModel::getMesh()
	{
		return mesh;
	}

	void IModel::setMesh( IMesh* _mesh )
	{
		mesh = _mesh;
	}

	IModel* IModel::addChild()
	{
		IModel* child = new IModel( renderer );

		child->parent = this;

		children.push_back( child );

		return child;
	}

	void IModel::addChild( IModel* _child )
	{
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
				_child->parent = NULL;

				children.erase( it );
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

		matrixIdentity( matWorld );
		
		matrixMultiply( matWorld, matWorld, matSize );
		matrixMultiply( matWorld, matWorld, matAngle );
		matrixMultiply( matWorld, matWorld, matCenter );

		if ( parent )
			matrixMultiply( matWorld, matWorld, parent->getWorldMatrix() );

		dirty = false;
	}

	void IModel::render()
	{
		for ( vector<IModel*>::iterator it = children.begin() ; it != children.end() ; ++it )
		{
			(*it)->render();
		}
	}
}