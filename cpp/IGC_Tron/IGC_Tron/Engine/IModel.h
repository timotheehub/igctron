
#pragma once

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "IMesh.h"
#include "Common.h"

#include <vector>

using namespace std;

/***********************************************************************************/

namespace IGC
{
	class IRenderer;

	class IModel
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	protected:

		IRenderer* renderer;

		IModel* parent;

		vector<IModel*> children;

		float3 center;
		float3 angle;
		float3 size;
		
		float4x4 matCenter;
		float4x4 matAngle;
		float4x4 matSize;

		float4x4 matWorld;
		
		IMesh* mesh;

		bool dirty;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		IModel( IRenderer* _renderer );
		virtual ~IModel();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		IMesh* getMesh();
		void setMesh( IMesh* _mesh );

		virtual IModel* addChild();
		void addChild( IModel* _child );
		void delChild( IModel* _child );
		IModel* getChild( int _id );
		int getChildCount();

		void move( float _x, float _y, float _z );
		void rotate( float _x, float _y, float _z );
		void grow( float _x, float _y, float _z );
		void shrink( float _x, float _y, float _z );

		void setCenter( float _x, float _y, float _z );
		void setCenter( float3& _center );
		float3 getCenter() { return center; };

		void setAngle( float _x, float _y, float _z );
		void setAngle( float3& _angle ) ;
		float3 getAngle() { return angle; };

		void setSize( float _x, float _y, float _z );
		void setSize( float3 & _size );
		float3 getSize() { return size; };

		float pitch() { return angle.x; };
		float yaw() { return angle.y; };
		float roll() { return angle.z;  };

		float x() { return center.x; };
		float y() { return center.y; };
		float z() { return center.z; };

		float width() { return size.x; };
		float height() { return size.y; };
		float depth() { return size.z; };

		float4x4 getWorldMatrix();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
		update()
			Force la mise à jour des matrices.
		*/
		virtual void update();

		/*
		render()
			Rend le maillage de ce modèle ainsi que ceux de tous ses fils.
		*/
		virtual void render();

	};
}