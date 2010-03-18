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
			Lib�re les ressources.
		*/
		~IMaterial();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers le moteur associ� � cet objet.
		*/
		Engine* getEngine();

		/*
			Renvoie le renderer associ� � ce mat�riau.
		*/
		IRenderer* getRenderer();

		/*
			Renvoie la couleur diffuse associ�e � ce mat�riau.
		*/
		float4 getDiffuseColor()
		{
			return diffuse;
		}

		/*
			D�finit la couleur diffuse { _r, _g, _b, _a } associ�e � ce mat�riau.
		*/
		void setDiffuseColor( float _r, float _g, float _b, float _a )
		{
			diffuse = make_float4( _r, _g, _b, _a );
		}

		/*
			D�finit la couleur diffuse { _rgba } associ�e � ce mat�riau.
		*/
		void setDiffuseColor( float4 _rgba )
		{
			diffuse = _rgba;
		}

		/*
			D�finit la couleur diffuse { _rgba } associ�e � ce mat�riau.
		*/
		void setDiffuseColor( const float* _rgba )
		{
			diffuse = make_float4( _rgba[0], _rgba[1], _rgba[2], _rgba[3] );
		}

		/*
			Renvoie la couleur ambiante associ�e � ce mat�riau.
		*/
		float4 getAmbientColor()
		{
			return ambient;
		}

		/*
			D�finit la couleur ambiante { _r, _g, _b, _a } associ�e � ce mat�riau.
		*/
		void setAmbientColor( float _r, float _g, float _b, float _a )
		{
			ambient = make_float4( _r, _g, _b, _a );
		}

		/*
			D�finit la couleur ambiante { _rgba } associ�e � ce mat�riau.
		*/
		void setAmbientColor( float4 _rgba )
		{
			ambient = _rgba;
		}

		/*
			D�finit la couleur ambiante { _rgba } associ�e � ce mat�riau.
		*/
		void setAmbientColor( const float* _rgba )
		{
			ambient = make_float4( _rgba[0], _rgba[1], _rgba[2], _rgba[3] );
		}

		/*
			Renvoie la couleur speculaire associ�e � ce mat�riau.
		*/
		float4 getSpecularColor()
		{
			return specular;
		}

		/*
			D�finit la couleur speculaire { _r, _g, _b, _a } associ�e � ce mat�riau.
		*/
		void setSpecularColor( float _r, float _g, float _b, float _a )
		{
			specular = make_float4( _r, _g, _b, _a );
		}

		/*
			D�finit la couleur speculaire { _rgba } associ�e � ce mat�riau.
		*/
		void setSpecularColor( float4 _rgba )
		{
			specular = _rgba;
		}

		/*
			D�finit la couleur speculaire { _rgba } associ�e � ce mat�riau.
		*/
		void setSpecularColor( const float* _rgba )
		{
			specular = make_float4( _rgba[0], _rgba[1], _rgba[2], _rgba[3] );
		}

		/*
			Renvoie la couleur emissive associ�e � ce mat�riau.
		*/
		float4 getEmissiveColor()
		{
			return emissive;
		}

		/*
			D�finit la couleur emissive { _r, _g, _b, _a } associ�e � ce mat�riau.
		*/
		void setEmissiveColor( float _r, float _g, float _b, float _a )
		{
			emissive = make_float4( _r, _g, _b, _a );
		}

		/*
			D�finit la couleur emissive { _rgba } associ�e � ce mat�riau.
		*/
		void setEmissiveColor( float4 _rgba )
		{
			emissive = _rgba;
		}

		/*
			D�finit la couleur emissive { _rgba } associ�e � ce mat�riau.
		*/
		void setEmissiveColor( const float* _rgba )
		{
			emissive = make_float4( _rgba[0], _rgba[1], _rgba[2], _rgba[3] );
		}

		/*
			Renvoie la puissance de ce mat�riau.
		*/
		float getPower()
		{
			return power;
		}

		/*
			D�finit la puissance de ce mat�riau.
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
			Force la g�n�ration des ressources.
		*/
		virtual void update() = 0;

		/*
			Active ce mat�riau pour le prochain rendu.
		*/
		virtual void bind() = 0;

		/*
			Desactive le mat�riau pour le prochain rendu.
		*/
		virtual void unbind() = 0;
	};
}

/***********************************************************************************/

#endif
