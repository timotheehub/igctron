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

#ifndef _FACTORY
#define _FACTORY

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"
#include "Engine.h"

#include <iostream>
#include <google/dense_hash_map>

using google::dense_hash_map;
using std::tr1::hash; // or ext::hash, __gnu_cxx::hash, or maybe tr1::hash

/***********************************************************************************/

namespace IGC
{
	class Factory
	{

/***********************************************************************************/
/** CLASSES AMIES                                                                 **/
/***********************************************************************************/

		friend class Engine;

/***********************************************************************************/
/** TYPES                                                                         **/
/***********************************************************************************/

	private:

		struct eqstr
		{
			bool operator()( char* s1, char* s2 ) const
			{
				return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
			}
		};

		struct eqptr
		{
			bool operator()( void* p1, void* p2 ) const
			{
				return (p1 == p2);
			}
		};

		struct object
		{
			char* name;
			void* addr;

			uint counter;
		};

		typedef dense_hash_map<char*, object*, hash<char*>, eqstr> StringHashMap;
		typedef dense_hash_map<void*, object*, hash<void*>, eqptr> PointerHashMap;

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	private:

		Engine* engine;

		StringHashMap tableByName;
		PointerHashMap tableByAddr;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie cette classe dont le but est de centraliser la gestion des
			ressources en mémoire.
		*/
		Factory( Engine* _engine );

		/*
			Libère les ressources encore allouées en mémoire.
		*/
		~Factory();

/***********************************************************************************/
/** METHODES PRIVEES                                                              **/
/***********************************************************************************/

	private:

		char* generateName();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers le moteur associé à cette factory.
		*/
		Engine* getEngine();


/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Recherche un objet en fonction du nom passé en paramètre et renvoie son pointeur. Dans ce cas l'objet
			en question est marqué comme ayant une référence supplémentaire.
			Si le nom passé en paramètre n'est pas encore répertorié alors un nouvel objet est automatiquement
			instancié et associé à ce nom. L'objet est alors marqué comme référencé une fois.
			Si NULL est passé en paramètre alors un nom d'objet est automatiquement généré.
		*/
		Window* acquire( Window* addr, char* name );
		Renderer* acquire( Renderer* addr, char* name );
		Camera* acquire( Camera* addr, char* name );
		Font* acquire( Font* addr, char* name );
		Mesh* acquire( Mesh* addr, char* name );
		Model* acquire( Model* addr, char* name );

		/*
			Recherche un objet en fonction du pointeur passé en paramètre et renvoie ce même pointeur. Dans ce
			cas l'objet en question est marqué comme ayant une référence supplémentaire.
			Si NULL est passé en paramètre alors un objet est automatiquement instancié avec un nom aléatoire.
		*/
		Window* acquire( Window* addr );
		Renderer* acquire( Renderer* addr );
		Camera* acquire( Camera* addr );
		Font* acquire( Font* addr );
		Mesh* acquire( Mesh* addr );
		Model* acquire( Model* addr );

		/*
			Marque l'objet dont le nom est passé en paramètre comme ayant une référence en moins. Si l'objet en
			question n'est plus marqué comme référencé alors il est automatiquement détruit.
		*/
		void release( Window* addr );
		void release( Renderer* addr );
		void release( Camera* addr );
		void release( Font* addr );
		void release( Mesh* addr );
		void release( Model* addr );

	};
}

/***********************************************************************************/

#endif
