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

#ifndef _CAMERA
#define _CAMERA

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"
#include "Engine.h"
#include "IRenderer.h"

/***********************************************************************************/

namespace IGC
{

/***********************************************************************************/

	class ICamera
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	protected:

		Engine* engine;

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
			Instancie la classe en d�finissant une cam�ra situ�e au point { 0.0f, 0.0f, 0.0f } et
			regardant en direction de l'axe Z positif. Cette cam�ra est initialis�e pour un �cran 4/3 et
			dispose d'un champ de vision sur 90�.
		*/
		ICamera( Engine* _engine );

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers le moteur associ� � cet objet.
		*/
		Engine* getEngine();

		/*
			Renvoie le renderer associ� � ce mod�le.
		*/
		IRenderer* getRenderer();

		/*
			D�place cette cam�ra vers l'avant (d�fini par le vecteur direction) � une vitesse d�finie
			par le param�tre _speed.
		*/
		void moveForward( float _speed );
		void moveForward( double _speed ) { moveForward( (float)_speed ); };

		/*
			D�place cette cam�ra vers l'arri�re (d�fini par le vecteur oppos� � direction) � une vitesse
			d�finie par le param�tre _speed.
		*/
		void moveBackward( float _speed );
		void moveBackward( double _speed ) { moveBackward( (float)_speed ); };

		/*
			D�place cette cam�ra vers la gauche (d�fini par le vecteur perpendiculaire � la projection de
			direction sur le plan XZ) � une vitesse d�finie par le param�tre _speed.
		*/
		void moveLeft( float _speed );
		void moveLeft( double _speed ) { moveLeft( (float)_speed ); };

		/*
			D�place cette cam�ra vers la droite (d�fini par le vecteur perpendiculaire � la projection de
			direction sur le plan XZ) � une vitesse d�finie par le param�tre _speed.
		*/
		void moveRight( float _speed );
		void moveRight( double _speed ) { moveRight( (float)_speed ); };

		/*
			D�place cette cam�ra d'un certain nombre d'unit�s sur les axes X, Y, et Z.
		*/
		void translate( float _x, float _y, float _z );
		void translate( double _x, double _y, double _z ) { translate( (float)_x, (float)_y, (float)_z ); };

		/*
			Fait pivoter cette cam�ra d'un certain nombre de radians par rapport aux axes X, Y, et Z.
		*/
		void rotate( float _x, float _y, float _z );
		void rotate( double _x, double _y, double _z ) { rotate( (float)_x, (float)_y, (float)_z ); };

		/*
			T�l�porte cette cam�ra au point { _x, _y, _z } dans le rep�re global.
		*/
		void setCenter( float _x, float _y, float _z );
		void setCenter( double _x, double _y, double _z ) { setCenter( (float)_x, (float)_y, (float)_z ); };

		/*
			T�l�porte cette cam�ra au point { _center.x, _center.y, _center.z } dans le rep�re global.
		*/
		void setCenter( float3 _center );

		/*
			Renvoie la position de cette cam�ra dans le rep�re global.
		*/
		float3 getCenter() { return center; };

		/*
			Calcule et d�finit l'angle permettant � cette cam�ra d'observer l'objet situ� au
			point { _x, _y, _z } dans le rep�re global.
		*/
		void lookAt( float _x, float _y, float _z );
		void lookAt( double _x, double _y, double _z ) { lookAt( (float)_x, (float)_y, (float)_z ); };

		/*
			Calcule et d�finit l'angle permettant � cette cam�ra d'observer l'objet situ� au
			point { _center.x, _center.y, _center.z } dans le rep�re global.
		*/
		void lookAt( float3 _point );

		/*
			Renvoie le vecteur direction normalis� de cette cam�ra.
		*/
		float3 getDir() { return dir; };

		/*
			D�finit les angles (en radians) de cette cam�ra par rapport aux axes X (tangage),
			Y (lacet), et Z (roulis).
		*/
		void setAngle( float _x, float _y, float _z );
		void setAngle( double _x, double _y, double _z ) { setAngle( (float)_x, (float)_y, (float)_z ); };

		/*
			D�finit les angles (en radians) de cette cam�ra par rapport aux axes X (tangage),
			Y (lacet), et Z (roulis).
		*/
		void setAngle( float3 _angle );

		/*
			Renvoie un vecteur contenant les angles (en radians) de cette cam�ra par rapport
			aux axes X (tangage), Y (lacet), et Z (roulis).
		*/
		float3 getAngle() { return angle; };

		/*
			D�finit l'angle d'ouverture (champ de vision) de cette cam�ra.
		*/
		void setFOV( float _fov );
		void setFOV( double _fov ) { setFOV( (float)_fov ); };

		/*
			Revoie l'angle d'ouverture (champ de vision) de cette cam�ra.
		*/
		float getFOV() { return fov; };

		/*
			D�finit le rapport largeur/hauteur de l'�cran destin� � cette cam�ra.
		*/
		void setRatio( float _ratio );
		void setRatio( double _ratio ) { setRatio( (float)_ratio ); };

		/*
			D�finit le rapport largeur/hauteur de l'�cran destin� � cette cam�ra.
		*/
		void setRatio( int _width, int _height );

		/*
			Renvoie le rapport largeur/hauteur de l'�cran destin� � cette cam�ra.
		*/
		float getRatio() { return ratio; };

		/*
			D�finit la distance autoris�e par rapport au plan rapproch� (plus cette distance est faible
			plus on augmente les d�tails situ�s au premier plan).
		*/
		void setZNearPlane( float _zNearPlane );
		void setZNearPlane( double _zNearPlane ) { setZNearPlane( (float)_zNearPlane ); };

		/*
			Renvoie la distance autoris�e par rapport au plan rapproch�.
		*/
		float getZNearPlane() { return zNearPlane; };

		/*
			D�finit la distance autoris�e par rapport au plan �loign� (plus cette distance est grande
			plus on augmente les d�tails situ�s � l'arri�re plan).
		*/
		void setZFarPlane( float _zFarPlane );
		void setZFarPlane( double _zFarPlane ) { setZFarPlane( (float)_zFarPlane ); };

		/*
			Renvoie la distance autoris�e par rapport au plan �loign�.
		*/
		float getZFarPlane() { return zFarPlane; };

		/*
			Renvoie l'angle (en radians) de cette cam�ra par rapport � l'axe X (tangage).
		*/
		float pitch() { return angle.x; };

		/*
			Renvoie l'angle (en radians) de cette cam�ra par rapport � l'axe Y (lacet).
		*/
		float yaw() { return angle.y; };

		/*
			Renvoie l'angle (en radians) de cette cam�ra par rapport � l'axe Z (roulis).
		*/
		float roll() { return angle.z;  };

		/*
			Renvoie la position (en u) de cette cam�ra sur l'axe X dans le rep�re global.
		*/
		float x() { return center.x; };

		/*
			Renvoie la position (en u) de cette cam�ra sur l'axe Y dans le rep�re global.
		*/
		float y() { return center.y; };

		/*
			Renvoie la position (en u) de cette cam�ra sur l'axe Z dans le rep�re global.
		*/
		float z() { return center.z; };

		/*
			Renvoie la direction de cette cam�ra sur l'axe X.
		*/
		float dx() { return dir.x; };

		/*
			Renvoie la direction de cette cam�ra sur l'axe X.
		*/
		float dy() { return dir.y; };

		/*
			Renvoie la direction de cette cam�ra sur l'axe X.
		*/
		float dz() { return dir.z; };

		/*
			Renvoie la matrice de transformation vers l'espace de la cam�ra.
		*/
		float4x4 getViewMatrix();

		/*
			Renvoie la matrice de projection sur l'�cran.
		*/
		float4x4 getProjMatrix();

		/*
			Renvoie la matrice inverse de transformation vers l'espace de la cam�ra.
		*/
		float4x4 getInvViewMatrix();

		/*
			Renvoie la matrice inverse de projection sur l'�cran.
		*/
		float4x4 getInvProjMatrix();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Force la mise � jour des matrices.
		*/
		virtual void update();

		/*
			Active cette cam�ra pour le prochain rendu.
		*/
		virtual void bind() = 0;

	};
}

/***********************************************************************************/

#endif
