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

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Debug.h"

/***********************************************************************************/
/** OPERATEURS                                                                    **/
/***********************************************************************************/
#ifdef _WIN32
	#ifdef _DEBUG

		void* operator new( size_t nSize, const char* lpszFileName, int nLine )
		{
			return ::operator new( nSize, 1, lpszFileName, nLine );
		}

		void operator delete( void* p, const char* lpszFileName, int nLine )
		{
			return ::operator delete( p, 1, lpszFileName, nLine );
		}

	#endif // _DEBUG
#endif // _WIN32

/***********************************************************************************/
/** CONSTANTES                                                                    **/
/***********************************************************************************/

#define DEBUG_OUTPUT_LENGTH 256

/***********************************************************************************/
/** FONCTIONS                                                                     **/
/***********************************************************************************/

void debugPrint ( const char* _format, ... )
{
#ifdef _DEBUG

	va_list list;
	va_start( list, _format );

	static char buffer[DEBUG_OUTPUT_LENGTH] = {0};

#ifdef _WIN32
	#ifdef __STDC_WANT_SECURE_LIB__
		vsprintf_s( buffer, DEBUG_OUTPUT_LENGTH, _format, list );
	#else //__STDC_WANT_SECURE_LIB__
		StringCbVPrintf( buffer, DEBUG_OUTPUT_LENGTH, _format, list );
	#endif //__STDC_WANT_SECURE_LIB__

	OutputDebugString( buffer );
#else
	vfprintf( stderr, _format, list );
#endif // _WIN32

	va_end( list );

#endif //_DEBUG
}

void debugMemoryLeaks ( )
{
#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif // _WIN32
}
