// Displayer.cpp
// Definition de la classe Displayer

#include "Displayer.h"
#include "Menu.h"
#include "Game.h"
using namespace IGC;

bool Displayer::running = true;
const float WALL_WIDTH = 0.15;

/******************************************************************************
*                      Gestion des evenements                                 *
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

void Displayer::RegisterMouseMove ( IGC::IWindow::LPMOUSEMOVECALLBACK _callback )
{
	window->registerMouseMoveCallback ( _callback );
}

void Displayer::UnregisterMouseMove ( IGC::IWindow::LPMOUSEMOVECALLBACK _callback )
{
	window->unregisterMouseMoveCallback ( _callback );
}

double Displayer::GetTime ( )
{
	return engine->getTime ( );
}

double Displayer::GetDelta ( )
{
	return engine->getDelta ( );
}

/******************************************************************************
*                      Methodes Get et Set                                    *
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
	/* Vehicles */
	Model* model = factory->acquire( (IGC::Model*)NULL, "model_motorbike" );
	Material* material = factory->acquire((IGC::Material*)NULL,
			"vehicle_material");

	model->import( "greyMBike.3ds" ); // TODO : Supprimer les 2 dumpings objects de 0 bytes
	model->shrink( 4.0f, 4.0f, 4.0f );

	material->setDiffuseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	material->setAmbientColor( 0.0f, 1.0f, 0.0f, 1.0f );
	material->setSpecularColor( 1.0f, 1.0f, 1.0f, 1.0f );
	material->setEmissiveColor( 1.0f, 1.0f, 1.0f, 1.0f );

	/* Textures */
	IGC::Texture* texture = factory->acquire( (IGC::Texture*)NULL,
			"back_screen_menu" );
	texture->import( "warp.png" );
	
	texture = factory->acquire( (IGC::Texture*)NULL, "plane_tile" );
	texture->import( "plane.png" );

	/* Modèle du plan de jeu */
	model = factory->acquire( (IGC::Model*)NULL, "model_plane" );
	model->setCenter( 10.0f, 0.0f, 15.0f );
	IGC::Mesh * mesh = factory->acquire( (IGC::Mesh*)NULL, "mesh_plane" );
	mesh->createPlane( 1, 1, 20.0f, 30.0f );
	mesh->update ( );
	model->setMesh( mesh );
	model->grow( 20.0f, 1.0f, 30.0f );
	factory->release ( mesh );

	/* Modèle des murs */
	mesh = factory->acquire( (IGC::Mesh*)NULL, "mesh_wall" );
	//mesh->createPlane( 1.0f, 1.0f, 1.0f, 1.0f );
	mesh->createCube( 1.0f, WALL_WIDTH, 1.0f );
	mesh->update ( );
	model = factory->acquire( (IGC::Model*)NULL, "model_wallX" );
	model->setMesh( mesh );
	model->rotate ( PI / 2.0f, 0.0f, 0.0f );
	model = factory->acquire( (IGC::Model*)NULL, "model_wallZ" );
	model->setMesh( mesh );
	model->rotate ( PI / 2.0f, PI / 2.0f, 0.0f );
	factory->release ( mesh );

	material = factory->acquire((IGC::Material*)NULL, "wall_material");
	// NB : à terme je remplacerai l'évaluation de la lumière actuellement par fonction fixe en utilisant des shaders

	// la couleur diffuse est la couleur diffusée par l'objet lorsqu'une lumière est présente dans la scène
	// sans intérêt dans le cas présent
	material->setDiffuseColor( 1.0f, 1.0f, 1.0f, 1.0f );

	// la couleur ambiante est une couleur indépendante des lumières dans la scène, elle est multipliée par la couleur de l'objet,
	// donnée par sa texture par exemple, donc s'il n'y a pas de texture comme dans le cas du mur, il n'y a pas d'intérêt
	material->setAmbientColor( 0.0f, 1.0f, 0.0f, 1.0f );

	// la couleur spéculaire est la couleur réflechie par l'objet lorsqu'une lumière est présente dans la scène,
	// c'est ce qui donne l'effet de brillance métallique sur un objet, sans intérêt dans le cas présent
	material->setSpecularColor( 1.0f, 1.0f, 1.0f, 1.0f );

	// enfin la couleur emissive est une couleur indépendante des lumières dans la scène, mais contrairement à la couleur
	// ambiante qui est multipliée, celle-ci est additionnée en plus, c'est donc celle-ci qui t'intéresse dans le cas du mur,
	// les valeurs sont dans l'ordre R, G, B, A, sachant qu'il est préférable que A reste à 1
	material->setEmissiveColor( 1.0f, 1.0f, 1.0f, 1.0f );
}

void Displayer::UnloadScene()
{
	/* Modeles */
	Model* model = factory->acquire( (IGC::Model*)NULL, "model_motorbike" );
	factory->release( model );
	factory->release( model );
	model = factory->acquire( (IGC::Model*)NULL, "model_plane" );
	factory->release( model );
	factory->release( model );
	model = factory->acquire( (IGC::Model*)NULL, "model_wallX" );
	factory->release( model );
	factory->release( model );
	model = factory->acquire( (IGC::Model*)NULL, "model_wallZ" );
	factory->release( model );
	factory->release( model );
	
	/* Textures */
	IGC::Texture* texture = factory->acquire( (IGC::Texture*)NULL, "back_screen_menu" );
	factory->release( texture );
	factory->release( texture );
	texture = factory->acquire( (IGC::Texture*)NULL, "plane_tile" );
	factory->release( texture );	
	factory->release( texture );
}



/******************************************************************************
*                   Initialisation pour l'ecran                               *
******************************************************************************/
// Initialise l'ecran
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
	Menu *aMenu = Menu::GetInstance ( );
	aMenu->Free ( );
	aMenu->kill ( );
	freeRenderer ( );
	freeWindow ( );
	freeEngine ( );
}

// Libere renderer
void Displayer::freeRenderer ( )
{
	IGC::Font* font = factory->acquire( (IGC::Font*)NULL, "font_fps" );
	factory->release( font );
	factory->release( font ); 

	renderer->finalize();
	factory->release( renderer );
}
	
// Libere window
void Displayer::freeWindow ( )
{
	window->hide();
	window->unregisterCloseCallback( OnClose );

	factory->release( window );
}

// Libere engine
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
