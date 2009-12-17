// Menu.cpp
// Definition de la classe Menu
#include "Menu.h"
#include "Globals.h"
#include "Displayer.h"
#include "Game.h"
#include "Settings.h"
#include "Computer.h"

using namespace KeyCodes;

/******************************************************************************
*                    Gestion des evenements                                   *
******************************************************************************/
void Game::OnKeyDown( int keyboardContext, int keyCode )
{
	Game *aGame = Game::GetInstance ( );
	Menu *aMenu = Menu::GetInstance ( );
	aGame->MutexAcquireLock ( );
	Displayer *aDisplayer = Displayer::GetInstance ( );
	Settings *aSettings = Settings::GetInstance ( );
	const PlayerSettings *aPlayerSettings = aSettings->GetPlayerSettings ( 0 );
	switch ( keyCode )
	{
		case ESCAPE :
			aDisplayer->SetState ( Displayer::MENU );
			aGame->Free ( );
			aMenu->Init ( );
			break;
		default:
			if ( keyCode == aPlayerSettings->TurnLeft )
			{
				if ( aGame->tabPlayers[0] != 0 )
				{
					aGame->tabPlayers[0]->MoveLeft ( );
				}
			}
			else if ( keyCode == aPlayerSettings->TurnRight )
			{
				if ( aGame->tabPlayers[0] != 0 )
				{
					aGame->tabPlayers[0]->MoveRight( );
				}
			}
			printf("context : %d || code : %d\n", keyboardContext, keyCode);
			break;
	}	
	aGame->MutexReleaseLock ( );
}

void Game::OnKeyUp( int keyboardContext, int keyCode )
{

}

/******************************************************************************
*                              Mise a jour                                    *
******************************************************************************/
// Met a jour le menu
void Game::Update ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	double dt = aDisplayer->GetDelta ( );
	for ( int i = 0; i < nbPlayers; i++ )
	{
		tabPlayersIndex[i]->Update ( dt );
		// On verifie qu'il n'a fonce dans aucun mur.
		for ( int j = 0; j < nbPlayers; j++ )
		{
			tabPlayersIndex[i]->IsGettingKilled ( *tabPlayersIndex[j] );
		}
	}
}

/******************************************************************************
*                   Initialisation et destruction                             *
******************************************************************************/
// Initialisation le menu
void Game::Init ( )
{
	/********** Initialisation temporaire ******/
	const double SPEED = 5;

	PlayerInfos tabPlayersInfos [ MAX_PLAYERS ];
	Utils::CartesianVector tabPos [ MAX_PLAYERS ];
	Utils::CartesianVector tabDir [ MAX_PLAYERS ];

	tabPlayersInfos[0].ATypePlayer = PlayerInfos::KEYBOARD;
	tabPlayersInfos[0].Name = "Toto";
	tabPlayersInfos[1].ATypePlayer = PlayerInfos::COMPUTER;
	tabPlayersInfos[1].Name = "Tata";
	tabPlayersInfos[2].ATypePlayer = PlayerInfos::COMPUTER;
	tabPlayersInfos[2].Name = "Titi";
	tabPlayersInfos[3].ATypePlayer = PlayerInfos::COMPUTER;
	tabPlayersInfos[3].Name = "Tutu";

	tabPos[0].x = 15;
	tabPos[0].y = 0;
	tabPos[0].z = 25;
	tabPos[1].x = 5;
	tabPos[1].y = 0;
	tabPos[1].z = 25;
	tabPos[2].x = 5;
	tabPos[2].y = 0;
	tabPos[2].z = 5;
	tabPos[3].x = 15;
	tabPos[3].y = 0;
	tabPos[3].z = 5;

	tabDir[0].x = -SPEED;
	tabDir[0].y = 0;
	tabDir[0].z = 0;
	tabDir[1].x = 0;
	tabDir[1].y = 0;
	tabDir[1].z = -SPEED;
	tabDir[2].x = SPEED;
	tabDir[2].y = 0;
	tabDir[2].z = 0;
	tabDir[3].x = 0;
	tabDir[3].y = 0;
	tabDir[3].z = SPEED;
	/****** Fin d'initialisation temporaire ****/

	// Players
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->RegisterKeys ( OnKeyDown, OnKeyUp );
	nbPlayers = 0;
	for ( int i = 0; i < MAX_PLAYERS; i++ )
	{
		if ( tabPlayersInfos[ i ].ATypePlayer != PlayerInfos::NO )
		{
			if ( tabPlayersInfos[ i ].ATypePlayer == PlayerInfos::KEYBOARD )
			{
				tabPlayers [ i ] = new Player ( tabPlayersInfos[ i ].Name, tabPos[ i ], tabDir [ i ], i );
			}
			else
			{
				tabPlayers [ i ] = new Computer ( tabPlayersInfos[ i ].Name, tabPos[ i ], tabDir [ i ], i );
			}
			nbPlayers++;
		}
		else
		{
			tabPlayers [ i ] = 0;
		}
	}
	tabPlayersIndex = new Player * [ nbPlayers ];
	for ( int i = 0, j = 0; i < MAX_PLAYERS; i++ )
	{
		if ( tabPlayers [ i ] != 0 )
		{
			tabPlayersIndex [ j++ ] = tabPlayers [ i ];
		}
	}

	// Plane
	aPlane = new Plane;
}

// Lib�re le menu
void Game::Free ( )
{
	// Players
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->UnregisterKeys ( OnKeyDown, OnKeyUp );
	for ( int i = 0; i < MAX_PLAYERS; i++ )
	{
		delete tabPlayers [ i ];
	}
	delete [] tabPlayersIndex;

	// Plane
	delete aPlane;
}

/******************************************************************************
*                                Affichage                                    *
******************************************************************************/
void Game::Draw ( )
{
	aMutex.AcquireLock ( );

	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Renderer *renderer = aDisplayer->GetRenderer ( );
	IGC::Factory *factory = aDisplayer->GetFactory ( );

	renderer->clear( 0.0f, 0.0f, 0.1f, 1.0f );
	
	aPlane->Draw ( );

	for ( int i = 0; i < nbPlayers; i++ )
	{
		tabPlayersIndex[i]->Draw ( );
	}

	aMutex.ReleaseLock ( );
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
