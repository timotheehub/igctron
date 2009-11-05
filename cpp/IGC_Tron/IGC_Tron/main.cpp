/*#include <iostream>

int main( int argc, char** argv )
{
	std::cout << "Hello world." << std::endl;

	return 0;
}
*/
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
#include "Displayer.h"
#include "main.h"

#include "Common.h"

#ifdef _WIN32
	#pragma warning (disable : 4996)
#endif

/***********************************************************************************/
/** DEBUG                                                                         **/
/***********************************************************************************/

#include "Debug.h"

/***********************************************************************************/

using namespace IGC;


/***********************************************************************************/
/** EVENEMENTS                                                                    **/
/***********************************************************************************/

void onClose()
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->running = false;
}

/***********************************************************************************/
/** FONCTIONS                                                                     **/
/***********************************************************************************/

void mainLoop()
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->running = true;

	while( aDisplayer->running == true )
	{
		aDisplayer->UpdateGraphics ( );
	}
}





/***********************************************************************************/
/** POINT D'ENTREE                                                                **/
/***********************************************************************************/

int main( int argc, char **argv )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->InitScreen ( );

	aDisplayer->LoadScene();

	mainLoop();

	aDisplayer->UnloadScene();

	aDisplayer->FreeMemory ( );

	aDisplayer->kill ( );

	debugMemoryLeaks();

	return 0;
}

