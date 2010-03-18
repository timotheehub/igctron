// Menu.cpp
// Definition de la classe Menu
#include "Menu.h"
#include "Globals.h"
#include "Displayer.h"
#include "Game.h"
#include "Settings.h"
#include "Computer.h"
#include "CameraFree.h"
#include "CameraOverall.h"
#include "CameraPlayer.h"

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
	const CameraSettings *aCameraSettings = aSettings->GetCameraSettings ( );

	// Traitement de la touche
	switch ( keyCode )
	{
		case ESCAPE :
			aDisplayer->SetState ( Displayer::MENU );
			aGame->Free ( );
			aMenu->Init ( );
			break;
		default:
			// Touches de caméras
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
			// Touches de changement de caméras
			else if ( keyCode == aCameraSettings->PreviousCamera )
			{
				aGame->SetPreviousCamera();
			}
			else if ( keyCode == aCameraSettings->NextCamera )
			{
				aGame->SetNextCamera();
			}
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
void Game::Update( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	double dt = aDisplayer->GetDelta ( );

	// On met à jour les positions
	for ( int i = 0; i < nbPlayers; ++i )
	{
		tabPlayersIndex[i]->Update ( dt );
	}

	// On regarde qui est mort.
	for ( int i = 0 ; i < nbPlayers ; ++i )
	{
		for ( int j = 0 ; j < nbPlayers ; ++j )
		{
			if (tabPlayersIndex[i]->IsGettingKilled ( *tabPlayersIndex[j] ))
			{
				printf("Player %s died.", tabPlayersIndex[i]->GetName().c_str());
			}
		}
	}
}

/******************************************************************************
*                   Initialisation et destruction                             *
******************************************************************************/
// Initialisation le menu
void Game::Init( )
{
	/********** Initialisation temporaire ******/
	const double SPEED = 5;

	PlayerInfos tabPlayersInfos [ MAX_PLAYERS ];
	Utils::CartesianVector tabPos [ MAX_PLAYERS ];
	Utils::CartesianVector tabDir [ MAX_PLAYERS ];

	tabPlayersInfos[0].ATypePlayer = PlayerInfos::KEYBOARD;
	tabPlayersInfos[1].ATypePlayer = PlayerInfos::COMPUTER;
	tabPlayersInfos[2].ATypePlayer = PlayerInfos::COMPUTER;
	tabPlayersInfos[3].ATypePlayer = PlayerInfos::COMPUTER;

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

	// Gestion des touches claviers
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->RegisterKeys ( OnKeyDown, OnKeyUp );

	// Mise à jour de tabPlayers
	nbPlayers = 0;
	for ( int i = 0; i < MAX_PLAYERS; i++ )
	{
		if ( tabPlayersInfos[ i ].ATypePlayer != PlayerInfos::NO )
		{
			if ( tabPlayersInfos[ i ].ATypePlayer == PlayerInfos::KEYBOARD )
			{
				tabPlayers [ i ] = new Player ( tabPos[ i ], tabDir [ i ], i );
			}
			else
			{
				tabPlayers [ i ] = new Computer ( tabPos[ i ], tabDir [ i ], i );
			}
			nbPlayers++;
		}
		else
		{
			tabPlayers [ i ] = 0;
		}
	}

	// Mise à jour de tabPlayersIndex
	tabPlayersIndex = new Player * [ nbPlayers ];
	tabPlayersAlive = new bool [ nbPlayers ];
	for ( int i = 0, j = 0; i < MAX_PLAYERS; i++ )
	{
		if ( tabPlayers [ i ] != 0 )
		{
			tabPlayersIndex [ j++ ] = tabPlayers [ i ];
		}
	}

	// Plane
	aPlane = new Plane;

	// Gestion des cameras
	tabCameras[nCurrentCamera]->Init();
}

// Libere le menu
void Game::Free ( )
{
	// Gestion des touches
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->UnregisterKeys ( OnKeyDown, OnKeyUp );

	// Suppression des joueurs
	for ( int i = 0; i < MAX_PLAYERS; i++ )
	{
		delete tabPlayers [ i ];
	}
	delete [] tabPlayersIndex;
	delete [] tabPlayersAlive;

	// Plane
	delete aPlane;

	// Gestion des caméras
	tabCameras[nCurrentCamera]->Free();
}

/******************************************************************************
*                                Affichage                                    *
******************************************************************************/
void Game::Draw ( )
{
	aMutex.AcquireLock ( );

	tabCameras[nCurrentCamera]->Update();

	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Renderer *renderer = aDisplayer->GetRenderer ( );

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
	nCurrentCamera = 0;
	tabCameras[0] = new CameraOverall;
	tabCameras[1] = new CameraFree;
	tabCameras[2] = new CameraPlayer ( 0 );
}

// Destructeur
Game::~Game ( )
{
	for ( int i = 0; i < Game::MAX_CAMERAS; i++ )
	{
		delete tabCameras[i];
	}
}
