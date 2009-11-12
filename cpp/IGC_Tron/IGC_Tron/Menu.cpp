// Menu.cpp
// Définition de la classe Menu
#include "Menu.h"
#include "Globals.h"
#include "Displayer.h"

using namespace KeyCode;

/******************************************************************************
*                    Gestion des événements                                   *
******************************************************************************/
void Menu::OnKeyDown( int keyboardContext, int keyCode )
{
	switch ( keyCode )
	{
		case ESCAPE :
			Displayer::OnClose();
			break;
		case UP :
			break;
		case DOWN :
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
*                              Mise à jour                                    *
******************************************************************************/
// Met à jour le menu
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
	aDisplayer->RegisterKeys ( OnKeyDown, OnKeyUp );
}

// Libère le menu
void Menu::Free ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->UnregisterKeys ( OnKeyDown, OnKeyUp );
}

/******************************************************************************
*                 Constructeurs et destructeurs                               *
******************************************************************************/
// Constructeur
Menu::Menu ( )
{
	Init ( );
}

// Destructeur
Menu::~Menu ( )
{
	Free ( );
}