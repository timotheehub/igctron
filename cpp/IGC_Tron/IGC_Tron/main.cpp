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
#include "Menu.h"

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
/** FONCTIONS                                                                     **/
/***********************************************************************************/

void mainLoop()
{
	Displayer::StateEnum aState;
	Displayer *aDisplayer = Displayer::GetInstance ( );
	Displayer::SetRunning( true );

	while( Displayer::GetRunning() == true )
	{
		aDisplayer->UpdateGraphics ( );
		aState = aDisplayer->GetState ( );
		if ( aState == Displayer::MENU ) 
		{
			Menu *aMenu = Menu::GetInstance ( );
			aMenu->Update ( );
		}
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

