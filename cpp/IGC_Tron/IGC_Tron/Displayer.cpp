// Displayer.cpp
// D�finition de la classe Displayer

#include "Displayer.h"
#include "Menu.h"
#include "Game.h"
using namespace IGC;

bool Displayer::running = true;

/******************************************************************************
*                      Gestion des �venements                                 *
******************************************************************************/

void Displayer::OnClose ( )
{
	running = false;
}

void Displayer::RegisterKeys( IGC::IWindow::LPKEYDOWNCALLBACK _cbKeyDown,
							IGC::IWindow::LPKEYUPCALLBACK _cbKeyUp )
{
	window->registerKeyDownCallback ( _cbKeyDown );
	window->registerKeyUpCallback ( _cbKeyUp );
}

void Displayer::UnregisterKeys( IGC::IWindow::LPKEYDOWNCALLBACK _cbKeyDown,
							IGC::IWindow::LPKEYUPCALLBACK _cbKeyUp )
{
	window->unregisterKeyDownCallback ( _cbKeyDown );
	window->unregisterKeyUpCallback ( _cbKeyUp );
}

double Displayer::GetTime ( )
{
	return engine->getTime ( );
}

/******************************************************************************
*                      M�thodes Get et Set                                    *
******************************************************************************/
bool Displayer::GetRunning ( )
{
	return running;
}
	
void Displayer::SetRunning ( bool isRunning )
{
	running = isRunning;
}

Displayer::StateEnum Displayer::GetState ( )
{
	return state;
}

void Displayer::SetState ( Displayer::StateEnum aState )
{
	state = aState;
}

/******************************************************************************
*                   Chargement des ressources                                 *
******************************************************************************/
// Charge les ressources
void Displayer::LoadRessources ( )
{
}

void Displayer::LoadScene()
{
	Model* model = factory->acquire( (IGC::Model*)NULL, "model_ship1" );
	model->import( "ship.3ds" );
	model->shrink( 80.0f, 80.0f, 80.0f );
	Model* model2 = factory->acquire( (IGC::Model*)NULL, "model_ship2" );
	model2->Clone ( model );
	model2 = factory->acquire( (IGC::Model*)NULL, "model_ship3" );
	model2->Clone ( model );
	model2 = factory->acquire( (IGC::Model*)NULL, "model_ship4" );
	model2->Clone ( model );

	model = factory->acquire( (IGC::Model*)NULL, "model_cube" );
	Mesh* mesh = factory->acquire( (IGC::Mesh*)NULL, "mesh_cube" );
	mesh->createCube( 1, 1, 1 );
	mesh->update ( );
	model->setMesh( mesh );
	model->grow( 10.0f, 1.0f, 1.0f );

	IGC::Texture* texture = factory->acquire( (IGC::Texture*)NULL, "back_screen_menu" );
	texture->import( "warp.png" );
	
	texture = factory->acquire( (IGC::Texture*)NULL, "plane_tile" );
	texture->import( "plane.png" );

	model = factory->acquire( (IGC::Model*)NULL, "model_plane" );
	mesh = factory->acquire( (IGC::Mesh*)NULL, "mesh_plane" );
	mesh->createPlane( 1, 1 );
	mesh->update ( );
	model->setMesh( mesh );
	model->grow( 30.0f, 1.0f, 20.0f );
}

void Displayer::UnloadScene()
{
	IGC::Texture* texture = factory->acquire( (IGC::Texture*)NULL, "back_screen_menu" );
	factory->release( texture );
	Model* model = factory->acquire( (IGC::Model*)NULL, "model_ship" );
	factory->release( model );
}



/******************************************************************************
*                   Initialisation pour l'�cran                               *
******************************************************************************/
// Initialise l'�cran
void Displayer::InitScreen ( )
{
	state = MENU;
	initEngine ( );
	initWindow ( );
	initRenderer ( );
	Menu *aMenu = Menu::GetInstance ( );
	aMenu->Init ( );
}

// Initialise Engine
void Displayer::initEngine ( )
{
	engine = new Engine();
	factory = engine->getFactory();	
}

// Initialise window
void Displayer::initWindow ( )
{
	window = factory->acquire( (IGC::Window*)NULL );

	window->setLeft( 120 );
	window->setTop( 80 );
	window->setWidth( 1024 );
	window->setHeight( 768 );
	window->setTitle( "Tron" );

	window->registerCloseCallback( OnClose );

	window->show();
}
	
// Initialise renderer
void Displayer::initRenderer ( )
{
	renderer = factory->acquire( (IGC::Renderer*)NULL );
	renderer->disableFullscreen();
	renderer->disableVSync();
	renderer->useHardware();
	renderer->initialize();

	Camera* camera = factory->acquire( (IGC::Camera*)NULL, "camera_default" );
	camera->setRatio( window->getInnerWidth(), window->getInnerHeight() );
	camera->setCenter( 00.0f, 20.0f, 0.0f );
	camera->lookAt( 00.0f, -1.0f, 0.1f );
	camera->update();

	IGC::Font* font = factory->acquire( (IGC::Font*)NULL, "font_fps" );
	font->setName( "Verdana" );
	font->setSize( 12 );
	font->setBold( true );
	font->setItalic( false );
	font->update();
}



/******************************************************************************
*              Met a jour la partie la partie graphique                       *
******************************************************************************/
// Rafraichit graphiquement
void Displayer::UpdateGraphics ( )
{
	switch ( state )
	{
		case GAME:
			Game::GetInstance ( )->Draw ( );
			break;
		case MENU:
			Menu::GetInstance ( )->Draw ( );
			break;
	}
	DrawFps ( );

	renderer->update();

	engine->update();
}


/******************************************************************************
*                      Fonctions d'affichage                                  *
******************************************************************************/
// Affiche les fps
void Displayer::DrawFps ( )
{
	double cycleTime = 0;

	static char fpsBuffer[20];
	static char avgBuffer[20];

	IGC::Font* font = factory->acquire( (IGC::Font*)NULL, "font_fps" );
	font->bind();

	int x = renderer->toPointX( 0.01f );
	int y = renderer->toPointY( 0.01f );

	renderer->drawText( "tron", x, y, 1.0f, 1.0f, 1.0f, 1.0f );

	if ( engine->getCurrentFramerate() > 40 )
		renderer->drawText( fpsBuffer, x, y + 32, 0.0f, 1.0f, 0.0f, 1.0f );
	else if ( engine->getCurrentFramerate() > 20 )
		renderer->drawText( fpsBuffer, x, y + 32, 1.0f, 1.0f, 0.0f, 1.0f );
	else
		renderer->drawText( fpsBuffer, x, y + 32, 1.0f, 0.0f, 0.0f, 1.0f );

	if ( engine->getAverageFramerate() > 60 )
		renderer->drawText( avgBuffer, x, y + 48, 0.0f, 1.0f, 0.0f, 1.0f );
	else if ( engine->getAverageFramerate() > 20 )
		renderer->drawText( avgBuffer, x, y + 48, 1.0f, 1.0f, 0.0f, 1.0f );
	else
		renderer->drawText( avgBuffer, x, y + 48, 1.0f, 0.0f, 0.0f, 1.0f );

	if ( engine->getTime() > cycleTime )
	{
		sprintf( fpsBuffer, "fps : %.3f", engine->getCurrentFramerate() );
		sprintf( avgBuffer, "avg : %.3f", engine->getAverageFramerate() );

		cycleTime = engine->getTime() + 1.0;
	}
}

/******************************************************************************
*                        Libere la memoire                                    *
******************************************************************************/
// Libere la memoire 
void Displayer::FreeMemory ( )
{
	freeRenderer ( );
	freeWindow ( );
	freeEngine ( );
}

// Lib�re renderer
void Displayer::freeRenderer ( )
{
	IGC::Font* font = factory->acquire( (IGC::Font*)NULL, "font_fps" );
	factory->release( font );
	Camera* camera = factory->acquire( (IGC::Camera*)NULL, "camera_default" );
	factory->release( camera );
	renderer->finalize();
	factory->release( renderer );
}
	
// Lib�re window
void Displayer::freeWindow ( )
{
	window->hide();
	window->unregisterCloseCallback( OnClose );

	factory->release( window );
}

// Lib�re engine
void Displayer::freeEngine ( )
{
	factory = NULL;

	delete engine;
}



/******************************************************************************
*                 Constructeurs et destructeurs                               *
******************************************************************************/
// Constructeur
Displayer::Displayer ( )
: engine( 0 ), factory( 0 ), window( 0 ), renderer( 0 )
{
}

// Destructeur
Displayer::~Displayer ( )
{
}
