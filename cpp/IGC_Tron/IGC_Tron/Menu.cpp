// Menu.cpp
// Dï¿½finition de la classe Menu
#include "Menu.h"
#include "Game.h"
#include "Globals.h"
#include "Displayer.h"

using namespace KeyCodes;

/******************************************************************************
*                    Gestion des evenements                                   *
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
			aMenu->SetButtonPointer( static_cast<Menu::ButtonEnum>
					( ( aMenu->GetButtonPointer ( ) + BUTTON_COUNT - 1 ) % BUTTON_COUNT ) );
			break;
		case DOWN :
			aMenu->SetButtonPointer( static_cast<Menu::ButtonEnum>
					( ( aMenu->GetButtonPointer ( ) + 1 ) % BUTTON_COUNT ) );
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
*                         Méthodes Get et Set                                 *
******************************************************************************/
Menu::ButtonEnum Menu::GetButtonPointer ( )
{
	return nButtonPointer;
}
	
void Menu::SetButtonPointer ( Menu::ButtonEnum aButton )
{
	nButtonPointer = aButton;
}

/******************************************************************************
*                              Mise a jour                                    *
******************************************************************************/
// Met ï¿½ jour le menu
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

// Libï¿½re le menu
void Menu::Free ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->UnregisterKeys ( &Menu::OnKeyDown, &Menu::OnKeyUp );
}

/******************************************************************************
*                                Affichage                                    *
******************************************************************************/
void Menu::Draw ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Renderer *renderer = aDisplayer->GetRenderer ( );
	IGC::Factory *factory = aDisplayer->GetFactory ( );

	renderer->clear( 1.0f, 0.0f, 0.0f, 1.0f );

	Camera* camera = factory->acquire( (IGC::Camera*)NULL, "camera_default" );
	camera->bind();

	Texture* texture = factory->acquire( (IGC::Texture*)NULL, "back_screen_menu" );

	texture->bind();
			
	renderer->setTransparency( true );

	int x0 = renderer->toPointX( 0.00f );
	int x1 = renderer->toPointX( 1.00f );
	int y0 = renderer->toPointY( 0.00f );
	int y1 = renderer->toPointY( 1.00f );

	renderer->drawImage( x0, y0, x1, y1, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f );

	IGC::Font* font = factory->acquire( (IGC::Font*)NULL, "font_fps" );
	font->bind();
	int x = renderer->toPointX( 0.5f );
	int y = renderer->toPointY( 0.3f );
	switch ( nButtonPointer )
	{
		case SOLO:
			renderer->drawText( "solo", x, y, 1.0f, 0.0f, 0.0f, 1.0f );
			y = renderer->toPointY( 0.5f );
			renderer->drawText( "settings", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			y = renderer->toPointY( 0.7f );
			renderer->drawText( "quit", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			break;
		case SETTINGS:
			renderer->drawText( "solo", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			y = renderer->toPointY( 0.5f );
			renderer->drawText( "settings", x, y, 1.0f, 0.0f, 0.0f, 1.0f );
			y = renderer->toPointY( 0.7f );
			renderer->drawText( "quit", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			break;
		case QUIT:
			renderer->drawText( "solo", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			y = renderer->toPointY( 0.5f );
			renderer->drawText( "settings", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			y = renderer->toPointY( 0.7f );
			renderer->drawText( "quit", x, y, 1.0f, 0.0f, 0.0f, 1.0f );
			break;
	}
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
