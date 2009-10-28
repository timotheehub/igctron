
#ifndef _MESH
#define _MESH

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"
#include "BoundingBox.h"
#include "IRenderer.h"

/***********************************************************************************/

namespace IGC
{

/***********************************************************************************/

	class IRenderer;

	class IMesh
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	public:

		bool hasVertices;	// true si ce maillage contient des sommets
		bool hasNormals;	// true s'il contient des normales associées aux sommets
		bool hasColors;		// true s'il contient des couleurs
		bool hasTexcoords;	// true s'il contient des coordonnées de texture

	protected:

		IRenderer* renderer;

		uint vertexCount;
		uint faceCount;

		aabox box;

		float3* vertices;
		float3* normals;
		float4* colors;
		float2* texcoords;

		uint3* faces;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
		IMesh( IRenderer* _renderer )
			Instancie cette classe dont le but est de centraliser l'accès aux
			ressources relatives à un maillage 3d en mémoire système.
		*/
		IMesh( IRenderer* _renderer );

		/*
		~IMesh()
			Libère la mémoire système réservée aux ressources de ce maillage 3d.
		*/
		~IMesh();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
		setVertexCount( uint _count )
			Spécifie le nombre de sommets pour ce maillage et alloue la mémoire
			système nécessaire en fonction des propriétés hasXXXX.
		*/
		void setVertexCount( uint _count );

		/*
		getVertexCount()
			Renvoie le nombre de sommets de ce maillage.
		*/
		uint getVertexCount();

		/*
		setFaceCount( uint _count )
			Spécifie le nombre de faces pour ce maillage et alloue la mémoire
			système nécessaire.
		*/
		void setFaceCount( uint _count );

		/*
		getFaceCount()
			Renvoie le nombre de faces de ce maillage.
		*/
		uint getFaceCount();

		/*
		getVertexPointer()
			Renvoie un pointeur vers le premier élément du tableau de sommets ou
			NULL si celui-ci n'a pas encore été créé.
		*/
		float3* getVertexPointer();

		/*
		getNormalPointer()
			Renvoie un pointeur vers le premier élément du tableau de normales ou
			bien NULL si celui-ci n'a pas encore été créé.
		*/
		float3* getNormalPointer();

		/*
		getColorPointer()
			Renvoie un pointeur vers le premier élément du tableau de couleurs ou
			NULL si celui-ci n'a pas encore été créé.
		*/
		float4* getColorPointer();

		/*
		getTexcoordPointer()
			Renvoie un pointeur vers le premier élément du tableau de coordonnées
			de texture ou bien NULL si celui-ci n'a pas encore été créé.
		*/
		float2* getTexcoordPointer();

		/*
		getFacePointer()
			Renvoie un pointeur vers le premier élément du tableau de faces ou
			NULL si celui-ci n'a pas encore été créé.
		*/
		uint3* getFacePointer();

		/*
		setVertex( uint _id, float _x, float _y, float _z )
			Définit le sommet { _x, _y, _z } ayant pour indice _id dans le tableau.
			La boite englobante du maillage est mise à jour en conséquence.
		*/
		void setVertex( uint _id, float _x, float _y, float _z )
		{
			vertices[_id] = make_float3( _x, _y, _z );
		}

		/*
		setVertex( uint _id, float3 _xyz )
			Définit le sommet { _xyz } ayant pour indice _id dans le tableau. La boite
			englobante du maillage est mise à jour en conséquence.
		*/
		void setVertex( uint _id, float3 _xyz )
		{
			vertices[_id] = _xyz;
		}

		/*
		setVertex( uint _id, const float* _xyz )
			Définit le sommet { _xyz } ayant pour indice _id dans le tableau. La boite
			englobante du maillage est mise à jour en conséquence.
		*/
		void setVertex( uint _id, const float* _xyz )
		{
			vertices[_id] = make_float3( _xyz[0], _xyz[1], _xyz[2] );

			box.merge( vertices[_id] );
		}

		/*
		getVertex( uint _id )
			Renvoie le sommet ayant pour indice _id dans le tableau.
		*/
		float3 getVertex( uint _id )
		{
			return vertices[_id];
		}

		/*
		setNormal( uint _id, float _l, float _m, float _n )
			Définit la normale { _l, _m, _n } associée au sommet ayant pour indice _id
			dans le tableau.
		*/
		void setNormal( uint _id, float _l, float _m, float _n )
		{
			normals[_id] = normalize( make_float3( _l, _m, _n ) );
		}

		/*
		setNormal( uint _id, float3 _lmn )
			Définit la normale { _lmn } ayant pour indice _id dans le tableau.
		*/
		void setNormal( uint _id, float3 _lmn )
		{
			normals[_id] = normalize( _lmn );
		}

		/*
		setNormal( uint _id, const float* _lmn )
			Définit la normale { _lmn } ayant pour indice _id dans le tableau.
		*/
		void setNormal( uint _id, const float* _lmn )
		{
			normals[_id] = normalize( make_float3( _lmn[0], _lmn[1], _lmn[2] ) );
		}

		/*
		getNormal( uint _id )
			Renvoie la normale ayant pour indice _id dans le tableau.
		*/
		float3 getNormal( uint _id )
		{
			return normals[_id];
		}

		/*
		setColor( uint _id, float _r, float _g, float _b, float _a )
			Définit la couleur { _r, _g, _b, _a } associée au sommet ayant pour
			indice _id dans le tableau.
		*/
		void setColor( uint _id, float _r, float _g, float _b, float _a )
		{
			colors[_id] = make_float4( _r, _g, _b, _a );
		}

		/*
		setColor( uint _id, float4 _rgba )
			Définit la couleur { _rgba } ayant pour indice _id dans le tableau.
		*/
		void setColor( uint _id, float4 _rgba )
		{
			colors[_id] = _rgba;
		}

		/*
		setColor( uint _id, const float* _rgba )
			Définit la couleur { _rgba } ayant pour indice _id dans le tableau.
		*/
		void setColor( uint _id, const float* _rgba )
		{
			colors[_id] = make_float4( _rgba[0], _rgba[1], _rgba[2], _rgba[3] );
		}

		/*
		getColor( uint _id )
			Renvoie la couleur ayant pour indice _id dans le tableau.
		*/
		float4 getColor( uint _id )
		{
			return colors[_id];
		}

		/*
		setTexcoord( uint _id, float _u, float _v )
			Définit les coordonnées de texture { _u, _v } associée au sommet ayant
			pour indice _id dans	le tableau.
		*/
		void setTexcoord( uint _id, float _u, float _v )
		{
			texcoords[_id] = make_float2( _u, _v );
		}

		/*
		setTexcoord( uint _id, float2 _uv )
			Définit les coordonnées de texture { _uv } ayant pour indice _id
			dans le tableau.
		*/
		void setTexcoord( uint _id, float2 _uv )
		{
			texcoords[_id] = _uv;
		}

		/*
		setTexcoord( uint _id, const float* _uv )
			Définit les coordonnées de texture { _uv } ayant pour indice _id
			dans le tableau.
		*/
		void setTexcoord( uint _id, const float* _uv )
		{
			texcoords[_id] = make_float2( _uv[0], _uv[1] );
		}

		/*
		getTexcoord( uint _id )
			Renvoie les coordonnées de texture ayant pour indice _id dans le tableau.
		*/
		float2 getTexcoord( uint _id )
		{
			return texcoords[_id];
		}

		/*
		setFace( uint _id, uint _a, uint _b, uint _c )
			Définit la face ayant pour indice _id dans le tableau. Les paramètres
			_a, _b, et _c représentent les indices des tableaux de sommets, normales,
			couleurs...
		*/
		void setFace( uint _id, uint _a, uint _b, uint _c )
		{
			faces[_id] = make_uint3( _a, _b, _c );
		}

		/*
		getFace( uint _id )
			Renvoie la face ayant pour indice _id dans le tableau.
		*/
		uint3 getFace( uint _id )
		{
			return faces[_id];
		}

		/*
		getHitbox()
			Renvoie la boite englobante de ce maillage 3d.
		*/
		aabox getBoundingBox()
		{
			return box;
		}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

		/*
		createCube( float width = 10.0f, float height = 10.0f, float depth = 10.0f )
			Construit un maillage de cube aligné sur les axes X, Y, Z du repère global
			et dont la largeur, hauteur, et profondeur sont définies respectivement
			par les paramètres width, height, et depth.
		*/
		void createCube( float width = 10.0f, float height = 10.0f, float depth = 10.0f );

		
		/*
		update()
			Copie les données de ce maillage en mémoire vidéo selon l'API utilisée.
		*/
		virtual void update() = 0;

		/*
		render()
			Affiche ce maillage à l'écran en fonction de la configuration de renderer spécifiée.
		*/
		virtual void render() = 0;

	};
}

/***********************************************************************************/

#endif
