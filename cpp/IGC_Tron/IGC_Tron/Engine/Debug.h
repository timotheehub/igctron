
#ifndef __DEBUG__
#define __DEBUG__

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#ifdef _WIN32
	#include <windows.h>
	#include <stdio.h>
	#include <crtdbg.h>

	#ifndef __STDC_WANT_SECURE_LIB__
		#include <strsafe.h>
	#endif //__STDC_WANT_SECURE_LIB__
#endif

/***********************************************************************************/
/** FONCTIONS                                                                     **/
/***********************************************************************************/

/*
debugPrint( char* _format, ... )
	* sous Windows : affiche un message personnalis� dans l'onglet output de Visual Studio
	* sous UNIX : envoie un message personnalis� sur stderr
	-> les arguments � passer sont de m�me nature que lors de l'appel de la fonction printf()
*/
void debugPrint( char* _format, ... );

/*
debugMemoryLeaks()
	* sous Windows : affiche dans l'onglet output de Visual Studio l'ensemble des pointeurs
					 n'ayant pas �t� lib�r�s
	* sous UNIX : sans effet
	-> l'ent�te de debug doit �tre plac�e au d�but de chaque fichier source
*/
void debugMemoryLeaks();

/***********************************************************************************/
/** DEBUG                                                                         **/
/***********************************************************************************/

#ifdef _WIN32
	#ifdef _DEBUG

		void* operator new( size_t nSize, const char* lpszFileName, int nLine );
		void operator delete( void* p, const char* lpszFileName, int nLine );

		#define DEBUG_NEW new( THIS_FILE, __LINE__ )

		#define MALLOC_DBG( x ) _malloc_dbg( x, 1, THIS_FILE, __LINE__ );
		#define malloc( x ) MALLOC_DBG( x )

		#define REALLOC_DBG( x, y ) _realloc_dbg( x, y, 1, THIS_FILE, __LINE__ );
		#define realloc( x, y ) REALLOC_DBG( x, y )

		#define FREE_DBG( x ) _free_dbg( x, 1 );
		#define free( x ) FREE_DBG( x )

	#endif // _DEBUG
#endif // _WIN32

/***********************************************************************************/

#endif
