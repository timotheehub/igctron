// Menu.cpp
// D�finition de la classe Menu
#include "Game.h"
#include "Menu.h"
#include "Globals.h"
#include "Displayer.h"

using namespace KeyCodes;

/******************************************************************************
*                    Gestion des �v�nements                                   *
******************************************************************************/
void Game::OnKeyDown( int keyboardContext, int keyCode )
{
	Game *aGame = Game::GetInstance ( );
	Menu *aMenu = Menu::GetInstance ( );
	Displayer *aDisplayer = Displayer::GetInstance ( );
	switch ( keyCode )
	{
		case ESCAPE :
			aGame->Free ( );
			aMenu->Init ( );
			aDisplayer->SetState ( Displayer::MENU );
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
*                              Mise � jour                                    *
******************************************************************************/
// Met � jour le menu
void Game::Update ( )
{
	/*for ( int i = 0; i < NB_PLAYERS; i++ )
	{
	}*/
}

/******************************************************************************
*                   Initialisation et destruction                             *
******************************************************************************/
// Initialisation le menu
void Game::Init ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->RegisterKeys ( OnKeyDown, OnKeyUp );
//	nbPlayersIndex = 0;
	/*for ( int i = 0, j = 0; i < NB_PLAYERS; i++ )
	{
		tabPlayers [ i ] = new Player;
		nbPlayer
	}*/
}

// Lib�re le menu
void Game::Free ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->UnregisterKeys ( OnKeyDown, OnKeyUp );
	/*for ( int i = 0; i < NB_PLAYERS; i++ )
	{
		tabPlayers [ i ] = delete Player;
	}*/
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
