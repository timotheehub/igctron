// Menu.cpp
// D�finition de la classe Menu
#include "Globals.h"
#include "Displayer.h"
#include "Menu.h"
#include "Game.h"
#include "CameraOverall.h"

using namespace KeyCodes;

/******************************************************************************
*                    Gestion des evenements                                   *
******************************************************************************/
void Menu::OnKeyDown( int keyboardContext, int keyCode )
{
	Menu *aMenu = Menu::GetInstance ( );
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
			Game::GetInstance()->Init ( );
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
*                         M�thodes Get et Set                                 *
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
// Met a jour le menu
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
	currentCamera->Init ( );
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->RegisterKeys ( &Menu::OnKeyDown, &Menu::OnKeyUp );
}

// Libere le menu
void Menu::Free ( )
{
	currentCamera->Free ( );
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->UnregisterKeys ( &Menu::OnKeyDown, &Menu::OnKeyUp );
}

/******************************************************************************
*                                Affichage                                    *
******************************************************************************/
void Menu::Draw ( )
{
	currentCamera->UpdateGraphics();

	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Renderer *renderer = aDisplayer->GetRenderer ( );
	IGC::Factory *factory = aDisplayer->GetFactory ( );

	renderer->clear( 1.0f, 0.0f, 0.0f, 1.0f );

	Texture* texture = factory->acquire( (IGC::Texture*)NULL, "back_screen_menu" );
	texture->bind();
	factory->release ( texture );
			
	renderer->setTransparency( true );

	int x0 = renderer->toPointX( 0.00f );
	int x1 = renderer->toPointX( 1.00f );
	int y0 = renderer->toPointY( 0.00f );
	int y1 = renderer->toPointY( 1.00f );

	renderer->drawImage( x0, y0, x1, y1, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f );

	IGC::Font* font = factory->acquire( (IGC::Font*)NULL, "font_menu" );
	font->bind();
	factory->release( font );

	int x = renderer->toPointX( 0.8f );
	int y = renderer->toPointY( 0.1f );
	switch ( nButtonPointer )
	{
		case SOLO:
			renderer->drawText( "solo", x, y, 1.0f, 0.0f, 0.0f, 1.0f );
			y = renderer->toPointY( 0.2f );
			renderer->drawText( "settings", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			y = renderer->toPointY( 0.3f );
			renderer->drawText( "quit", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			break;
		case SETTINGS:
			renderer->drawText( "solo", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			y = renderer->toPointY( 0.2f );
			renderer->drawText( "settings", x, y, 1.0f, 0.0f, 0.0f, 1.0f );
			y = renderer->toPointY( 0.3f );
			renderer->drawText( "quit", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			break;
		case QUIT:
			renderer->drawText( "solo", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			y = renderer->toPointY( 0.2f );
			renderer->drawText( "settings", x, y, 1.0f, 1.0f, 1.0f, 1.0f );
			y = renderer->toPointY( 0.3f );
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
	currentCamera = &cameraOverall;
}

// Destructeur
Menu::~Menu ( )
{
	Game::kill ( );
}
