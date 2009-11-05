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

#ifdef _WIN32
	#include <google/dense_hash_map>
	using google::dense_hash_map;
	using std::tr1::hash; // or ext::hash, __gnu_cxx::hash, or maybe tr1::hash
#else
	#include <map>
	using std::map;
#endif

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

#ifdef _WIN32
		typedef dense_hash_map<char*, object*, hash<char*>, eqstr> StringHashMap;
		typedef dense_hash_map<void*, object*, hash<void*>, eqptr> PointerHashMap;
#else
		typedef map<char*, object*, eqstr> StringHashMap;
		typedef map<void*, object*, eqptr> PointerHashMap;
#endif

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
			ressources en m�moire.
		*/
		Factory( Engine* _engine );

		/*
			Lib�re les ressources encore allou�es en m�moire.
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
			Renvoie un pointeur vers le moteur associ� � cette factory.
		*/
		Engine* getEngine();


/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Recherche un objet en fonction du nom pass� en param�tre et renvoie son pointeur. Dans ce cas l'objet
			en question est marqu� comme ayant une r�f�rence suppl�mentaire.
			Si le nom pass� en param�tre n'est pas encore r�pertori� alors un nouvel objet est automatiquement
			instanci� et associ� � ce nom. L'objet est alors marqu� comme r�f�renc� une fois.
			Si NULL est pass� en param�tre alors un nom d'objet est automatiquement g�n�r�.
		*/
		Window* acquire( Window* addr, char* name );
		Renderer* acquire( Renderer* addr, char* name );
		Camera* acquire( Camera* addr, char* name );
		Font* acquire( Font* addr, char* name );
		Mesh* acquire( Mesh* addr, char* name );
		Model* acquire( Model* addr, char* name );

		/*
			Recherche un objet en fonction du pointeur pass� en param�tre et renvoie ce m�me pointeur. Dans ce
			cas l'objet en question est marqu� comme ayant une r�f�rence suppl�mentaire.
			Si NULL est pass� en param�tre alors un objet est automatiquement instanci� avec un nom al�atoire.
		*/
		Window* acquire( Window* addr );
		Renderer* acquire( Renderer* addr );
		Camera* acquire( Camera* addr );
		Font* acquire( Font* addr );
		Mesh* acquire( Mesh* addr );
		Model* acquire( Model* addr );

		/*
			Marque l'objet dont le nom est pass� en param�tre comme ayant une r�f�rence en moins. Si l'objet en
			question n'est plus marqu� comme r�f�renc� alors il est automatiquement d�truit.
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
