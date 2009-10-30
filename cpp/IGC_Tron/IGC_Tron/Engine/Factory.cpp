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

#pragma warning (disable : 4996)

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include <time.h>

#include "Common.h"
#include "Engine.h"
#include "Factory.h"
#include "W32Window.h"
#include "X11Window.h"
#include "D3DRenderer.h"
#include "D3DCamera.h"
#include "D3DMesh.h"
#include "D3DModel.h"
#include "D3DFont.h"
#include "OGLRenderer.h"
#include "OGLCamera.h"
#include "OGLMesh.h"
#include "OGLModel.h"
#include "OGLFont.h"

/***********************************************************************************/
/** DEBUG                                                                         **/
/***********************************************************************************/

#include "Debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***********************************************************************************/

namespace IGC
{

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	Factory::Factory( Engine* _engine )
	{
		engine = _engine;

		srand( (uint)time( NULL ) );

		tableByName.set_empty_key( "AAAAAAAAAAAA" );
		tableByAddr.set_empty_key( (void*)0x00000000 );
		tableByName.set_deleted_key( "ZZZZZZZZZZZZ" );
		tableByAddr.set_deleted_key( (void*)0xFFFFFFFF );
	}

	Factory::~Factory()
	{
		PointerHashMap::iterator it = tableByAddr.begin();

		while ( it != tableByAddr.end() )
		{
			object* o = it->second;

			free( o->name );

			delete o->addr;

			delete o;

			it++;
		}
	}

/***********************************************************************************/
/** METHODES PRIVEES                                                              **/
/***********************************************************************************/

	char* Factory::generateName()
	{
		static char name[13];

		name[ 0] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[ 1] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[ 2] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[ 3] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[ 4] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[ 5] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[ 6] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[ 7] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[ 8] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[ 9] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[10] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[11] = (rand() % 2) ? (65 + rand() % 26) : (48 + rand() % 10);
		name[12] = 0;

		return name;
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	Engine* Factory::getEngine()
	{
		return engine;
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

#define ACQUIRE_OBJECT_BY_NAME( Class )													\
																						\
	void* retval;																		\
																						\
	if ( name == NULL )																	\
		name = generateName();															\
																						\
	if ( tableByName.find( name ) != tableByName.end() )								\
	{																					\
		object* o = tableByName[name];													\
																						\
		o->counter++;																	\
																						\
		retval = o->addr;																\
	}																					\
	else																				\
	{																					\
		object* o = new object;															\
																						\
		o->counter = 1;																	\
		o->name = (char*)malloc( (strlen(name) + 1) * sizeof(char) );					\
		strcpy( o->name, name );														\
		o->addr = new Class( engine );													\
																						\
		tableByAddr[o->addr] = o;														\
		tableByName[o->name] = o;														\
																						\
		retval = o->addr;																\
	}																					\

#define ACQUIRE_OBJECT_BY_ADDR( Class )													\
																						\
	void* retval;																		\
																						\
	if ( ( addr != NULL ) && ( tableByAddr.find( addr ) != tableByAddr.end() ) )		\
	{																					\
		object* o = tableByAddr[addr];													\
																						\
		o->counter++;																	\
																						\
		retval = o->addr;																\
	}																					\
	else																				\
	{																					\
		char* name = generateName();													\
																						\
		object* o = new object;															\
																						\
		o->counter = 1;																	\
		o->name = (char*)malloc( (strlen(name) + 1) * sizeof(char) );					\
		strcpy( o->name, name );														\
		o->addr = new Class( engine );													\
																						\
		tableByAddr[o->addr] = o;														\
		tableByName[o->name] = o;														\
																						\
		retval = o->addr;																\
	}																					\

#define RELEASE_OBJECT_BY_ADDR( Class )													\
																						\
	if ( addr != NULL )																	\
	{																					\
		if ( tableByAddr.find( addr ) != tableByAddr.end() )							\
		{																				\
			object* o = tableByAddr[addr];												\
																						\
			o->counter--;																\
																						\
			if ( o->counter == 0 )														\
			{																			\
				tableByName.erase( o->name );											\
																						\
				free( o->name );														\
																						\
				tableByAddr.erase( o->addr );											\
																						\
				delete (Class*)o->addr;													\
																						\
				delete o;																\
			}																			\
		}																				\
	}																					\

#define DEFINE_FACTORY_FUNCTIONS( Class )												\
																						\
	Class* Factory::acquire( Class* addr, char* name )									\
	{																					\
		ACQUIRE_OBJECT_BY_NAME( Class );												\
																						\
		return (Class*)retval;															\
	}																					\
																						\
	Class* Factory::acquire( Class* addr )												\
	{																					\
		ACQUIRE_OBJECT_BY_ADDR( Class );												\
																						\
		return (Class*)retval;															\
	}																					\
																						\
	void Factory::release( Class* addr )												\
	{																					\
		RELEASE_OBJECT_BY_ADDR( Class );												\
	}																					\

DEFINE_FACTORY_FUNCTIONS( Window );
DEFINE_FACTORY_FUNCTIONS( Renderer );
DEFINE_FACTORY_FUNCTIONS( Camera );
DEFINE_FACTORY_FUNCTIONS( Font );
DEFINE_FACTORY_FUNCTIONS( Mesh );
DEFINE_FACTORY_FUNCTIONS( Model );

}
