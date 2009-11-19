// Menu.cpp
// Définition de la classe Menu
#include "Game.h"
#include "Menu.h"
#include "Globals.h"
#include "Displayer.h"

using namespace KeyCode;

/******************************************************************************
*                    Gestion des événements                                   *
******************************************************************************/
void Game::OnKeyDown( int keyboardContext, int keyCode )
{
	Game *aGame = Game::GetInstance ( );
	Menu *aMenu = Menu::GetInstance ( );
	switch ( keyCode )
	{
		case ESCAPE :
			aGame->Free ( );
			aMenu->Init ( );
			break;
		default:
			printf("context : %d || code : %d\n", keyboardContext, keyCode);
			break;
	}	
}

void Game::OnKeyUp( int keyboardContext, int keyCode )
{

}

/******************************************************************************
*                              Mise à jour                                    *
******************************************************************************/
// Met à jour le menu
void Game::Update ( )
{
}

/******************************************************************************
*                   Initialisation et destruction                             *
******************************************************************************/
// Initialisation le menu
void Game::Init ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->RegisterKeys ( OnKeyDown, OnKeyUp );
}

// Libère le menu
void Game::Free ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->UnregisterKeys ( OnKeyDown, OnKeyUp );
}

/******************************************************************************
*                 Constructeurs et destructeurs                               *
******************************************************************************/
// Constructeur
Game::Game ( )
{
}

// Destructeur
Game::~Game ( )
{
}