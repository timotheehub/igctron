
#ifndef _CAMERA
#define _CAMERA

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"
#include "IRenderer.h"

/***********************************************************************************/

namespace IGC
{

/***********************************************************************************/

	class IRenderer;

	class ICamera
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	protected:

		IRenderer* renderer;

		float fov;
		float ratio;

		float zNearPlane;
		float zFarPlane;

		float3 dir;

		float3 center;
		float3 angle;

		float4x4 matView;
		float4x4 matProj;
		float4x4 matInvView;
		float4x4 matInvProj;

		bool dirty;

/***********************************************************************************/
/** METHODES PRIVEES                                                              **/
/***********************************************************************************/

	private:

		inline void dirFromAngle();
		inline void angleFromDir();
		
/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
		ICamera( IRenderer* _renderer )
			Instancie la classe en d�finissant une cam�ra situ�e au point
			{ 0.0f, 0.0f, 0.0f } et regardant en direction de l'axe Z positif. Cette
			cam�ra est initialis�e pour un �cran 4/3 et dispose d'un champ de vision
			sur 90�.
		*/
		ICamera( IRenderer* _renderer );

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
		moveForward( float _speed )
			D�place cette cam�ra vers l'avant (d�fini par le vecteur direction) �
			une vitesse d�finie par le param�tre _speed.
		*/
		void moveForward( float _speed );

		/*
		moveBackward( float _speed )
			D�place cette cam�ra vers l'arri�re (d�fini par le vecteur oppos� �
			direction) � une vitesse d�finie par le param�tre _speed.
		*/
		void moveBackward( float _speed );

		/*
		moveLeft( float _speed )
			D�place cette cam�ra vers la gauche (d�fini par le vecteur perpendiculaire
			� la projection de direction sur le plan XZ) � une vitesse d�finie par le
			param�tre _speed.
		*/
		void moveLeft( float _speed );

		/*
		moveRight( float _speed )
			D�place cette cam�ra vers la droite (d�fini par le vecteur perpendiculaire
			� la projection de direction sur le plan XZ) � une vitesse d�finie par le
			param�tre _speed.
		*/
		void moveRight( float _speed );

		/*
		translate( float _x, float _y, float _z )
			D�place cette cam�ra d'un certain nombre d'unit�s sur les axes X, Y, et Z.
		*/
		void translate( float _x, float _y, float _z );

		/*
		rotate( float _x, float _y, float _z )
			Fait pivoter cette cam�ra d'un certain nombre de radians par rapport aux
			axes X, Y, et Z.
		*/
		void rotate( float _x, float _y, float _z );

		/*
		setCenter( float _x, float _y, float _z )
			T�l�porte cette cam�ra au point { _x, _y, _z } dans le rep�re global.
		*/
		void setCenter( float _x, float _y, float _z );

		/*
		setCenter( float3 _center )
			T�l�porte cette cam�ra au point { _center.x, _center.y, _center.z } dans
			le rep�re global.
		*/
		void setCenter( float3 _center );

		/*
		getCenter()
			Renvoie la position de cette cam�ra dans le rep�re global.
		*/
		float3 getCenter() { return center; };

		/*
		lookAt( float _x, float _y, float _z )
			Calcule et d�finit l'angle permettant � cette cam�ra d'observer l'objet
			situ� au point { _x, _y, _z } dans le rep�re global.
		*/
		void lookAt( float _x, float _y, float _z );

		/*
		lookAt( float3 _point )
			Calcule et d�finit l'angle permettant � cette cam�ra d'observer l'objet
			situ� au point { _center.x, _center.y, _center.z } dans le rep�re global.
		*/
		void lookAt( float3 _point );

		/*
		getDir()
			Renvoie le vecteur direction normalis� de cette cam�ra.
		*/
		float3 getDir() { return dir; };

		/*
		setAngle( float _x, float _y, float _z )
			D�finit les angles (en radians) de cette cam�ra par rapport aux
			axes X (tangage), Y (lacet), et Z (roulis).
		*/
		void setAngle( float _x, float _y, float _z );

		/*
		setAngle( float3 _angle )
			D�finit les angles (en radians) de cette cam�ra par rapport aux
			axes X (tangage), Y (lacet), et Z (roulis).
		*/
		void setAngle( float3 _angle );

		/*
		getAngle()
			Renvoie un vecteur contenant les angles (en radians) de cette cam�ra
			par rapport aux axes X (tangage), Y (lacet), et Z (roulis).
		*/
		float3 getAngle() { return angle; };

		/*
		setFOV( float _fov )
			D�finit l'angle d'ouverture (champ de vision) de cette cam�ra.
		*/
		void setFOV( float _fov );

		/*
		getFOV()
			Revoie l'angle d'ouverture (champ de vision) de cette cam�ra.
		*/
		float getFOV() { return fov; };

		/*
		setRatio( float _ratio )
			D�finit le rapport largeur/hauteur de l'�cran destin� � cette cam�ra.
		*/
		void setRatio( float _ratio );

		/*
		setRatio( int _width, int _height )
			D�finit le rapport largeur/hauteur de l'�cran destin� � cette cam�ra.
		*/
		void setRatio( int _width, int _height );

		/*
		getRatio()
			Renvoie le rapport largeur/hauteur de l'�cran destin� � cette cam�ra.
		*/
		float getRatio() { return ratio; };

		/*
		setZNearPlane( float _zNearPlane )
			D�finit la distance autoris�e par rapport au plan rapproch� (plus cette
			distance est faible plus on augmente les d�tails situ�s au premier plan).
		*/
		void setZNearPlane( float _zNearPlane );

		/*
		getZNearPlane()
			Renvoie la distance autoris�e par rapport au plan rapproch�.
		*/
		float getZNearPlane() { return zNearPlane; };

		/*
		setZFarPlane( float _zFarPlane )
			D�finit la distance autoris�e par rapport au plan �loign� (plus cette
			distance est grande plus on augmente les d�tails situ�s � l'arri�re plan).
		*/
		void setZFarPlane( float _zFarPlane );

		/*
		getZFarPlane()
			Renvoie la distance autoris�e par rapport au plan �loign�.
		*/
		float getZFarPlane() { return zFarPlane; };

		/*
		pitch()
			Renvoie l'angle (en radians) de cette cam�ra par rapport � l'axe X (tangage).
		*/
		float pitch() { return angle.x; };

		/*
		yaw()
			Renvoie l'angle (en radians) de cette cam�ra par rapport � l'axe Y (lacet).
		*/
		float yaw() { return angle.y; };

		/*
		roll()
			Renvoie l'angle (en radians) de cette cam�ra par rapport � l'axe Z (roulis).
		*/
		float roll() { return angle.z;  };

		/*
		x()
			Renvoie la position (en u) de cette cam�ra sur l'axe X dans le rep�re global.
		*/
		float x() { return center.x; };

		/*
		y()
			Renvoie la position (en u) de cette cam�ra sur l'axe Y dans le rep�re global.
		*/
		float y() { return center.y; };

		/*
		z()
			Renvoie la position (en u) de cette cam�ra sur l'axe Z dans le rep�re global.
		*/
		float z() { return center.z; };

		/*
		dx()
			Renvoie la direction de cette cam�ra sur l'axe X.
		*/
		float dx() { return dir.x; };

		/*
		dy()
			Renvoie la direction de cette cam�ra sur l'axe X.
		*/
		float dy() { return dir.y; };

		/*
		dz()
			Renvoie la direction de cette cam�ra sur l'axe X.
		*/
		float dz() { return dir.z; };

		/*
		getViewMatrix()
			Renvoie la matrice de transformation vers l'espace de la cam�ra.
		*/
		float4x4 getViewMatrix();

		/*
		getProjMatrix()
			Renvoie la matrice de projection sur l'�cran.
		*/
		float4x4 getProjMatrix();

		/*
		getInvViewMatrix()
			Renvoie la matrice inverse de transformation vers l'espace de la cam�ra.
		*/
		float4x4 getInvViewMatrix();

		/*
		getInvProjMatrix()
			Renvoie la matrice inverse de projection sur l'�cran.
		*/
		float4x4 getInvProjMatrix();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
		update()
			Force la mise � jour des matrices.
		*/
		virtual void update();

		/*
		bind()
			Active cette cam�ra pour le prochain rendu.
		*/
		virtual void bind() = 0;

	};
}

/***********************************************************************************/

#endif
