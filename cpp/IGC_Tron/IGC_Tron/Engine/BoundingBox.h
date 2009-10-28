
#ifndef _BOUNDINGBOX
#define _BOUNDINGBOX

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

/***********************************************************************************/

namespace IGC
{
	struct aabox
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

		float3 min;
		float3 max;

/***********************************************************************************/
/** METHODES                                                                      **/
/***********************************************************************************/

		/*
		getArea()
			Renvoie la surface (en u²) calculée pour cette boite englobante.
		*/
		inline float getArea() const
		{
			float3 v = max - min;

			const float area = 2.f * ( v.x * v.y
									 + v.x * v.z
									 + v.y * v.z );

			return area;
		}

		/*
		reset()
			Réinitialise cette boite englobante comme "négative" (min > max).
		*/
		inline void reset()
		{
			min = make_float3( +INF );
			max = make_float3( -INF );
		}
	    
		/*
		reset( const float4& v )
			Réinitialise cette boite englobante comme "ponctuelle" en fonction du
			point passé en paramètre.
		*/
		inline void reset( const float3& v )
		{
			min = v;
			max = v;
		}

		/*
		reset( const float3& _min, const float3& _max )
			Réinitialise cette boite englobante à l'aide des points minimum et
			maximum passés en paramètre.
		*/
		inline void reset( const float3& _min, const float3& _max )
		{
			min = _min;
			max = _max;
		}

		/*
		merge( const aabox& b )
			Met à jour cette boite en englobant celle passée en paramètre.
		*/
		inline void merge( const aabox& b )
		{
			min = fminf( min, b.min );
			max = fmaxf( max, b.max );
		}

		/*
		merge( const float4& v )
			Met à jour cette boite en englobant le point passé en paramètre.
		*/
		inline void merge( const float3& v )
		{
			min = fminf( min, v );
			max = fmaxf( max, v );
		}

		/*
		merge( const float3& _min, const float3& _max )
			Met à jour cette boite en englobant les points minimum et maximum
			passés en paramètre.
		*/
		inline void merge( const float3& _min, const float3& _max )
		{
			min = fminf( min, _min );
			max = fmaxf( max, _max );
		}

/***********************************************************************************/
/** OPERATEURS                                                                    **/
/***********************************************************************************/

		/*
		operator=( const aabox& b )
			Copie dans cette boite englobante le contenu de celle située à droite
			de l'opérateur =.
		*/
		inline aabox& operator=( const aabox& b )
		{
			min = b.min;
			max = b.max;

			return *this;
		}
	    
	};

	typedef aabox BoundingBox;

}

/***********************************************************************************/

#endif
