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

#ifndef _MATERIAL
#define _MATERIAL

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

	class IMaterial
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	protected:

		Engine* engine;

		IRenderer* renderer;

		bool dirty;

		float4 diffuse;
		float4 ambient;
		float4 specular;
		float4 emissive;
		float power;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Copie
		*/
		void Clone( IMaterial * material );

		/*
			Instancie la classe.
		*/
		IMaterial( Engine* _engine );

		/*
			Libère les ressources.
		*/
		~IMaterial();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers le moteur associé à cet objet.
		*/
		Engine* getEngine();

		/*
			Renvoie le renderer associé à ce matériau.
		*/
		IRenderer* getRenderer();

		/*
			Renvoie la couleur diffuse associée à ce matériau.
		*/
		float4 getDiffuseColor()
		{
			return diffuse;
		}

		/*
			Définit la couleur diffuse { _r, _g, _b, _a } associée à ce matériau.
		*/
		void setDiffuseColor( float _r, float _g, float _b, float _a )
		{
			diffuse = make_float4( _r, _g, _b, _a );
		}

		/*
			Définit la couleur diffuse { _rgba } associée à ce matériau.
		*/
		void setDiffuseColor( float4 _rgba )
		{
			diffuse = _rgba;
		}

		/*
			Définit la couleur diffuse { _rgba } associée à ce matériau.
		*/
		void setDiffuseColor( const float* _rgba )
		{
			diffuse = make_float4( _rgba[0], _rgba[1], _rgba[2], _rgba[3] );
		}

		/*
			Renvoie la couleur ambiante associée à ce matériau.
		*/
		float4 getAmbientColor()
		{
			return ambient;
		}

		/*
			Définit la couleur ambiante { _r, _g, _b, _a } associée à ce matériau.
		*/
		void setAmbientColor( float _r, float _g, float _b, float _a )
		{
			ambient = make_float4( _r, _g, _b, _a );
		}

		/*
			Définit la couleur ambiante { _rgba } associée à ce matériau.
		*/
		void setAmbientColor( float4 _rgba )
		{
			ambient = _rgba;
		}

		/*
			Définit la couleur ambiante { _rgba } associée à ce matériau.
		*/
		void setAmbientColor( const float* _rgba )
		{
			ambient = make_float4( _rgba[0], _rgba[1], _rgba[2], _rgba[3] );
		}

		/*
			Renvoie la couleur speculaire associée à ce matériau.
		*/
		float4 getSpecularColor()
		{
			return specular;
		}

		/*
			Définit la couleur speculaire { _r, _g, _b, _a } associée à ce matériau.
		*/
		void setSpecularColor( float _r, float _g, float _b, float _a )
		{
			specular = make_float4( _r, _g, _b, _a );
		}

		/*
			Définit la couleur speculaire { _rgba } associée à ce matériau.
		*/
		void setSpecularColor( float4 _rgba )
		{
			specular = _rgba;
		}

		/*
			Définit la couleur speculaire { _rgba } associée à ce matériau.
		*/
		void setSpecularColor( const float* _rgba )
		{
			specular = make_float4( _rgba[0], _rgba[1], _rgba[2], _rgba[3] );
		}

		/*
			Renvoie la couleur emissive associée à ce matériau.
		*/
		float4 getEmissiveColor()
		{
			return emissive;
		}

		/*
			Définit la couleur emissive { _r, _g, _b, _a } associée à ce matériau.
		*/
		void setEmissiveColor( float _r, float _g, float _b, float _a )
		{
			emissive = make_float4( _r, _g, _b, _a );
		}

		/*
			Définit la couleur emissive { _rgba } associée à ce matériau.
		*/
		void setEmissiveColor( float4 _rgba )
		{
			emissive = _rgba;
		}

		/*
			Définit la couleur emissive { _rgba } associée à ce matériau.
		*/
		void setEmissiveColor( const float* _rgba )
		{
			emissive = make_float4( _rgba[0], _rgba[1], _rgba[2], _rgba[3] );
		}

		/*
			Renvoie la puissance de ce matériau.
		*/
		float getPower()
		{
			return power;
		}

		/*
			Définit la puissance de ce matériau.
		*/
		void setPower( float _power )
		{
			power = _power;
		}

/***********************************************************************************/
/** METHODES PRIVEES                                                              **/
/***********************************************************************************/

	protected:

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Force la génération des ressources.
		*/
		virtual void update() = 0;

		/*
			Active ce matériau pour le prochain rendu.
		*/
		virtual void bind() = 0;

		/*
			Desactive le matériau pour le prochain rendu.
		*/
		virtual void unbind() = 0;
	};
}

/***********************************************************************************/

#endif
