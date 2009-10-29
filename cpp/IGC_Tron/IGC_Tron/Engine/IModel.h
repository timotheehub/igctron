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

#ifndef _MODEL
#define _MODEL

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

		/*
			Instancie la classe en définissant un modèle 3d situé au point { 0.0f, 0.0f, 0.0f },
			orienté en direction de l'axe X positif, et de taille normale. Ce modèle est défini
			isolé, sans parent ni enfant, et n'a pas de maillage associé.
		*/
		IModel( IRenderer* _renderer );

		/*
			Détruit tous les enfants de ce modèle 3d.
		*/
		virtual ~IModel();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie le maillage associé à ce modèle 3d.
		*/
		IMesh* getMesh();

		/*
			Spécifie un maillage pour ce modèle 3d.
		*/
		void setMesh( IMesh* _mesh );

		/*
			Ajoute un fils à ce modèle.
		*/
		void addChild( IModel* _child );

		/*
			Détruit l'un des fils de ce modèle, si ce dernier se trouve dans la liste.
		*/
		void delChild( IModel* _child );

		/*
			Renvoie le fils ayant pour indice _id dans la liste.
		*/
		IModel* getChild( int _id );

		/*
			Renvoie le nombre de fils qu'a ce modèle 3d.
		*/
		int getChildCount();

		/*
			Déplace ce modèle d'un certain nombre d'unités sur les axes X, Y, et Z.
		*/
		void move( float _x, float _y, float _z );

		/*
			Fait pivoter ce modèle d'un certain nombre de radians par rapport aux axes X, Y, et Z.
		*/
		void rotate( float _x, float _y, float _z );

		/*
			Grossit ce modèle d'un certain nombre d'unités sur les axes X, Y, et Z.
		*/
		void grow( float _x, float _y, float _z );

		/*
			Réduit ce modèle d'un certain nombre d'unités par rapport aux axes X, Y, et Z.
		*/
		void shrink( float _x, float _y, float _z );

		/*
			Téléporte ce modèle 3d au point { _x, _y, _z } dans le repère global.
		*/
		void setCenter( float _x, float _y, float _z );

		/*
			Téléporte ce modèle au point { _center.x, _center.y, _center.z } dans le repère global.
		*/
		void setCenter( float3& _center );

		/*
			Renvoie la position de ce modèle 3d dans le repère global.
		*/
		float3 getCenter() { return center; };

		/*
			Définit les angles (en radians) de ce modèle 3d par rapport aux axes X (tangage),
			Y (lacet), et Z (roulis).
		*/
		void setAngle( float _x, float _y, float _z );

		/*
			Définit les angles (en radians) de ce modèle 3d par rapport aux axes X (tangage),
			Y (lacet), et Z (roulis).
		*/
		void setAngle( float3& _angle ) ;

		/*
			Renvoie un vecteur contenant les angles (en radians) de ce modèle par rapport
			aux axes X (tangage), Y (lacet), et Z (roulis).
		*/
		float3 getAngle() { return angle; };

		/*
			Spécifie la taille de ce modèle 3d par rapport aux axes X, Y, et Z. Une taille
			normale équivaut aux paramètres _x = 1.0f, _y = 1.0f, et _z = 1.0f.
		*/
		void setSize( float _x, float _y, float _z );

		/*
			Spécifie la taille de ce modèle 3d par rapport aux axes X, Y, et Z. Une taille
			normale équivaut au paramètre _size = { 1.0f, 1.0f, 1.0f }.
		*/
		void setSize( float3 & _size );

		/*
			Renvoie un vecteur contenant les rapports de taille (en multiple de u) de ce modèle
			par rapport	aux axes X, Y, et Z.
		*/
		float3 getSize() { return size; };

		/*
			Renvoie l'angle (en radians) de ce modèle 3d par rapport à l'axe X (tangage).
		*/
		float pitch() { return angle.x; };

		/*
			Renvoie l'angle (en radians) de ce modèle 3d par rapport à l'axe Y (lacet).
		*/
		float yaw() { return angle.y; };

		/*
			Renvoie l'angle (en radians) de ce modèle 3d par rapport à l'axe Z (roulis).
		*/
		float roll() { return angle.z;  };

		/*
			Renvoie la position (en u) de ce modèle 3d sur l'axe X dans le repère global.
		*/
		float x() { return center.x; };

		/*
			Renvoie la position (en u) de ce modèle 3d sur l'axe Y dans le repère global.
		*/
		float y() { return center.y; };

		/*
			Renvoie la position (en u) de ce modèle 3d sur l'axe Z dans le repère global.
		*/
		float z() { return center.z; };

		/*
			Renvoie le rapport de taille (en u) de ce modèle 3d sur l'axe X (largeur).
		*/
		float width() { return size.x; };

		/*
			Renvoie le rapport de taille (en u) de ce modèle 3d sur l'axe Y (hauteur).
		*/
		float height() { return size.y; };

		/*
			Renvoie le rapport de taille (en u) de ce modèle 3d sur l'axe Z (profondeur).
		*/
		float depth() { return size.z; };

		/*
			Renvoie la matrice permettant de transformer l'ensemble des coordonnées de
			ce modèle 3d depuis son propre repère vers le repère global.
		*/
		float4x4 getWorldMatrix();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Force la mise à jour de la matrice.
		*/
		virtual void update();

		/*
			Rend le maillage de ce modèle ainsi que ceux de tous ses fils.
		*/
		virtual void render();

	};
}

/***********************************************************************************/

#endif
