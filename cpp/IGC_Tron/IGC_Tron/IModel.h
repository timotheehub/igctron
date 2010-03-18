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
#include "Engine.h"
#include "IRenderer.h"

#include <vector>

using namespace std;

/***********************************************************************************/

namespace IGC
{
	class IModel
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	protected:

		Engine* engine;

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
			Instancie la classe en d?finissant un mod?le 3d situ? au point { 0.0f, 0.0f, 0.0f },
			orient? en direction de l'axe X positif, et de taille normale. Ce mod?le est d?fini
			isol?, sans parent ni enfant, et n'a pas de maillage associ?.
		*/
		IModel( Engine* _engine );

		/*
			D?truit tous les enfants de ce mod?le 3d.
		*/
		virtual ~IModel();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers le moteur associ? ? cet objet.
		*/
		Engine* getEngine();

		/*
			Renvoie le renderer associ? ? ce mod?le.
		*/
		IRenderer* getRenderer();

		/*
			Cr?e un nouveau maillage pour ce mod?le 3d puis le renvoie.
		*/
		IMesh* newMesh();

		/*
			Renvoie le maillage associ? ? ce mod?le 3d.
		*/
		IMesh* getMesh();

		/*
		 * Renvoie la BoundingBox de ce modele (celle du mesh ou des enfants)
		*/
		BoundingBox getBoundingBox ();

		/*
			Sp?cifie un maillage pour ce mod?le 3d.
		*/
		void setMesh( IMesh* _mesh );

		/*
			Cr?e un nouveau fils pour ce mod?le puis le renvoie.
		*/
		IModel* newChild();

		/*
			Ajoute un fils ? ce mod?le.
		*/
		void addChild( IModel* _child );

		/*
			D?truit l'un des fils de ce mod?le, si ce dernier se trouve dans la liste.
		*/
		void delChild( IModel* _child );

		/*
			Renvoie le fils ayant pour indice _id dans la liste.
		*/
		IModel* getChild( int _id );

		/*
			Renvoie le nombre de fils qu'a ce mod?le 3d.
		*/
		int getChildCount();

		/*
			D?place ce mod?le d'un certain nombre d'unit?s sur les axes X, Y, et Z.
		*/
		void move( float _x, float _y, float _z );

		/*
			Fait pivoter ce mod?le d'un certain nombre de radians par rapport aux axes X, Y, et Z.
		*/
		void rotate( float _x, float _y, float _z );

		/*
			Grossit ce mod?le d'un certain nombre d'unit?s sur les axes X, Y, et Z.
		*/
		void grow( float _x, float _y, float _z );

		/*
			R?duit ce mod?le d'un certain nombre d'unit?s par rapport aux axes X, Y, et Z.
		*/
		void shrink( float _x, float _y, float _z );

		/*
			T?l?porte ce mod?le 3d au point { _x, _y, _z } dans le rep?re global.
		*/
		void setCenter( float _x, float _y, float _z );

		/*
			T?l?porte ce mod?le au point { _center.x, _center.y, _center.z } dans le rep?re global.
		*/
		void setCenter( float3& _center );

		/*
			Renvoie la position de ce mod?le 3d dans le rep?re global.
		*/
		float3 getCenter() { return center; };

		/*
			D?finit les angles (en radians) de ce mod?le 3d par rapport aux axes X (tangage),
			Y (lacet), et Z (roulis).
		*/
		void setAngle( float _x, float _y, float _z );

		/*
			D?finit les angles (en radians) de ce mod?le 3d par rapport aux axes X (tangage),
			Y (lacet), et Z (roulis).
		*/
		void setAngle( float3& _angle ) ;

		/*
			Renvoie un vecteur contenant les angles (en radians) de ce mod?le par rapport
			aux axes X (tangage), Y (lacet), et Z (roulis).
		*/
		float3 getAngle() { return angle; };

		/*
			Sp?cifie la taille de ce mod?le 3d par rapport aux axes X, Y, et Z. Une taille
			normale ?quivaut aux param?tres _x = 1.0f, _y = 1.0f, et _z = 1.0f.
		*/
		void setSize( float _x, float _y, float _z );

		/*
			Sp?cifie la taille de ce mod?le 3d par rapport aux axes X, Y, et Z. Une taille
			normale ?quivaut au param?tre _size = { 1.0f, 1.0f, 1.0f }.
		*/
		void setSize( float3 & _size );

		/*
			Renvoie un vecteur contenant les rapports de taille (en multiple de u) de ce mod?le
			par rapport	aux axes X, Y, et Z.
		*/
		float3 getSize() { return size; };

		/*
			Renvoie l'angle (en radians) de ce mod?le 3d par rapport ? l'axe X (tangage).
		*/
		float pitch() { return angle.x; };

		/*
			Renvoie l'angle (en radians) de ce mod?le 3d par rapport ? l'axe Y (lacet).
		*/
		float yaw() { return angle.y; };

		/*
			Renvoie l'angle (en radians) de ce mod?le 3d par rapport ? l'axe Z (roulis).
		*/
		float roll() { return angle.z;  };

		/*
			Renvoie la position (en u) de ce mod?le 3d sur l'axe X dans le rep?re global.
		*/
		float x() { return center.x; };

		/*
			Renvoie la position (en u) de ce mod?le 3d sur l'axe Y dans le rep?re global.
		*/
		float y() { return center.y; };

		/*
			Renvoie la position (en u) de ce mod?le 3d sur l'axe Z dans le rep?re global.
		*/
		float z() { return center.z; };

		/*
			Renvoie le rapport de taille (en u) de ce mod?le 3d sur l'axe X (largeur).
		*/
		float width() { return size.x; };

		/*
			Renvoie le rapport de taille (en u) de ce mod?le 3d sur l'axe Y (hauteur).
		*/
		float height() { return size.y; };

		/*
			Renvoie le rapport de taille (en u) de ce mod?le 3d sur l'axe Z (profondeur).
		*/
		float depth() { return size.z; };

		/*
			Renvoie la matrice permettant de transformer l'ensemble des coordonn?es de
			ce mod?le 3d depuis son propre rep?re vers le rep?re global.
		*/
		float4x4 getWorldMatrix();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Copie
		*/
		void Clone( IModel * model );

		/*
			Force la mise ? jour de la matrice.
		*/
		virtual void update();

		/*
			Rend le maillage de ce mod?le ainsi que ceux de tous ses fils.
		*/
		virtual void render();

		/*
			Charge un fichier au format 3D Studio (*.3ds).
		*/
		void import( const char* _path );

	};
}

/***********************************************************************************/

#endif
