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

#ifndef _FONT
#define _FONT

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

	class IFont
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	protected:

		Engine* engine;

		IRenderer* renderer;

		char* name;
		
		int size;

		bool bold;
		bool italic;

		bool dirty;
		
/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie la classe en définissant une police "Verdana" de taille 12.
		*/
		IFont( Engine* _engine );

		/*
			Libère les ressources.
		*/
		~IFont();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers le moteur associé à cet objet.
		*/
		Engine* getEngine();

		/*
			Renvoie le renderer associé à ce modèle.
		*/
		IRenderer* getRenderer();

		/*
			Spécifie le nom de la police à utiliser.
		*/
		void setName( char* _name );

		/*
			Renvoie le nom de la police utilisée.
		*/
		char* getName() { return name; };

		/*
			Spécifie la taille de la police.
		*/
		void setSize( int _size );

		/*
			Renvoie la taille de la police.
		*/
		int getSize() { return size; };

		/*
			Spécifie si la police est en gras ou non.
		*/
		void setBold( bool _bold );

		/*
			Renvoie true si la police est en gras.
		*/
		bool getBold() { return bold; };

		/*
			Spécifie si la police est en italique ou non.
		*/
		void setItalic( bool _italic );

		/*
			Renvoie true si la police est en italique.
		*/
		bool getItalic() { return italic; };

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Force la génération des ressources pour cette police.
		*/
		virtual void update() = 0;

		/*
			Active cette police pour le prochain rendu.
		*/
		virtual void bind() = 0;

	};
}

/***********************************************************************************/

#endif
