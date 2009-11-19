// Menu.cpp
// D�finition de la classe Menu
#include "Menu.h"
#include "Game.h"
#include "Globals.h"
#include "Displayer.h"

using namespace KeyCodes;

/******************************************************************************
*                    Gestion des �v�nements                                   *
******************************************************************************/
void Menu::OnKeyDown( int keyboardContext, int keyCode )
{
	Menu *aMenu = Menu::GetInstance ( );
	Game *aGame = Game::GetInstance ( );
	Displayer *aDisplayer = Displayer::GetInstance ( );
	switch ( keyCode )
	{
		case ESCAPE :
			aMenu->Free ( );
			Displayer::OnClose();
			break;
		case UP :
			break;
		case DOWN :
			break;
		case ENTER :
			aMenu->Free ( );
			aGame->Init ( );
			aDisplayer->SetState ( Displayer::GAME );
			break;
		default:
			printf("context : %d || code : %d\n", keyboardContext, keyCode);
			break;
	}	

}

void Menu::OnKeyUp( int keyboardContext, int keyCode )
{

}

/******************************************************************************
*                              Mise � jour                                    *
******************************************************************************/
// Met � jour le menu
void Menu::Update ( )
{
}

/******************************************************************************
*                   Initialisation et destruction                             *
******************************************************************************/
// Initialisation le menu
void Menu::Init ( )
{
	nButtonPointer = SOLO;
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->RegisterKeys ( &Menu::OnKeyDown, &Menu::OnKeyUp );
}

// Lib�re le menu
void Menu::Free ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->UnregisterKeys ( &Menu::OnKeyDown, &Menu::OnKeyUp );
}

/******************************************************************************
*                 Constructeurs et destructeurs                               *
******************************************************************************/
// Constructeur
Menu::Menu ( )
{
}

// Destructeur
Menu::~Menu ( )
{
}
