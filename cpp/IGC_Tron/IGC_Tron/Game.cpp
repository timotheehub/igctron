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
	for ( int i = 0; i < nbPlayers; i++ )
	{
		//tabPlayersIndex[i].Update ( );
	}
}

/******************************************************************************
*                   Initialisation et destruction                             *
******************************************************************************/
// Initialisation le menu
void Game::Init ( )
{
	PlayerInfos tabPlayersInfos [ MAX_PLAYERS ];// Temp
	Utils::CartesianVector aVector ( 1, 1, 1 ); // Temp

	// Players
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->RegisterKeys ( OnKeyDown, OnKeyUp );
	nbPlayers = 0;
	for ( int i = 0; i < MAX_PLAYERS; i++ )
	{
		if ( tabPlayersInfos[ i ].ATypePlayer != PlayerInfos::NO )
		{
			tabPlayers [ i ] = new Player ( "nom", aVector, aVector );
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
	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Renderer *renderer = aDisplayer->GetRenderer ( );
	IGC::Factory *factory = aDisplayer->GetFactory ( );

	renderer->clear( 1.0f, 0.0f, 0.0f, 1.0f );

	Camera* camera = factory->acquire( (IGC::Camera*)NULL, "camera_default" );
	camera->bind();
	
	aPlane->Draw ( );

	IGC::Model* model = factory->acquire( (IGC::Model*)NULL, "model_ship" );
	IGC::Texture* texture = factory->acquire( (IGC::Texture*)NULL, "back_screen_menu" );
	texture->bind();
	renderer->setTransparency( false );
	model->render();
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
