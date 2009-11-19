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
#else
	#include <boost/unordered_map.hpp>
	using boost::unordered_map;
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

		struct hashstr
		{
			size_t operator()( const char* s ) const 
			{
				const byte* p = (const byte*)s; 

				size_t hashval = 0; 

				while ( *p != '\0' ) hashval += *p++;

				return hashval; 
			}
		};

		struct eqstr
		{
			bool operator()( const char* s1, const char* s2 ) const
			{
				return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
			}
		};

		struct hashptr
		{
			size_t operator()( const void* p ) const 
			{
				return (size_t)p; 
			}
		};

		struct eqptr
		{
			bool operator()( const void* p1, const void* p2 ) const
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
		typedef dense_hash_map<const char*, object*, hashstr, eqstr> StringHashMap;
		typedef dense_hash_map<const void*, object*, hashptr, eqptr> PointerHashMap;
#else
		typedef unordered_map<const char*, object*, hashstr, eqstr> StringHashMap;
		typedef unordered_map<const void*, object*, hashptr, eqptr> PointerHashMap;
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
		Factory( Engine* const _engine );

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
		Window* acquire( Window* addr, const char* name );
		Renderer* acquire( Renderer* addr, const char* name );
		Camera* acquire( Camera* addr, const char* name );
		Font* acquire( Font* addr, const char* name );
		Mesh* acquire( Mesh* addr, const char* name );
		Model* acquire( Model* addr, const char* name );
		Texture* acquire( Texture* addr, const char* name );

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
		Texture* acquire( Texture* addr );

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
		void release( Texture* addr );

	};
}

/***********************************************************************************/

#endif
