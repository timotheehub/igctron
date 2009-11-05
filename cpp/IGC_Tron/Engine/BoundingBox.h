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
			Renvoie la surface (en u�) calcul�e pour cette boite englobante.
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
			R�initialise cette boite englobante comme "n�gative" (min > max).
		*/
		inline void reset()
		{
			min = make_float3( +INF );
			max = make_float3( -INF );
		}
	    
		/*
			R�initialise cette boite englobante comme "ponctuelle" en fonction du point pass� en param�tre.
		*/
		inline void reset( const float3& v )
		{
			min = v;
			max = v;
		}

		/*
			R�initialise cette boite englobante � l'aide des points minimum et maximum pass�s en param�tre.
		*/
		inline void reset( const float3& _min, const float3& _max )
		{
			min = _min;
			max = _max;
		}

		/*
			Met � jour cette boite en englobant celle pass�e en param�tre.
		*/
		inline void merge( const aabox& b )
		{
			min = fminf( min, b.min );
			max = fmaxf( max, b.max );
		}

		/*
			Met � jour cette boite en englobant le point pass� en param�tre.
		*/
		inline void merge( const float3& v )
		{
			min = fminf( min, v );
			max = fmaxf( max, v );
		}

		/*
			Met � jour cette boite en englobant les points minimum et maximum pass�s en param�tre.
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
			Copie dans cette boite englobante le contenu de celle situ�e � droite de l'op�rateur =.
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
