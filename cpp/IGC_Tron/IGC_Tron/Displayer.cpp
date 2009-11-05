// Displayer.h
// D�claration de la classe Displayer

#include "Displayer.h"
/*


/******************************************************************************
*                   Chargement des ressources                                 *
******************************************************************************
// Charge les ressources
void Displayer::LoadRessources ( )
{
}



/******************************************************************************
*                   Initialisation pour l'�cran                               *
******************************************************************************
// Initialise l'�cran
void Displayer::InitScreen ( )
{
	initEngine ( );
	initWindow ( );
	initRenderer ( );
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
	window = new Window( engine );

	window->setLeft( 120 );
	window->setTop( 80 );
	window->setWidth( 1024 );
	window->setHeight( 768 );
	window->setTitle( "Tron" );

	window->registerCloseCallback( onClose );
	window->registerKeyDownCallback( onKeyDown );
	window->registerKeyUpCallback( onKeyUp );
	window->registerMouseMoveCallback( onMouseMove );

	window->show();
}
	
// Initialise renderer
void Displayer::initRenderer ( )
{
	renderer = factory->acquire( (Renderer*)NULL );

	renderer->disableFullscreen();
	renderer->disableVSync();
	renderer->useHardware();

	renderer->initialize();

	camera = factory->acquire( (Camera*)NULL );

	camera->setRatio( window->getInnerWidth(), window->getInnerHeight() );
	camera->setCenter( 0.0f, 30.0f, 10.0f );
	camera->lookAt( 0.0f, 0.0f, -50.0f );
	camera->update();

	font = factory->acquire( (Font*)NULL );

	font->setName( "Verdana" );
	font->setSize( 12 );
	font->setBold( true );
	font->setItalic( false );
	font->update();
}



/******************************************************************************
*              Met � jour la partie la partie graphique                       *
******************************************************************************
// Rafra�chit graphiquement
void Displayer::UpdateGraphics ( )
{
}



/******************************************************************************
*                        Lib�re la m�moire                                    *
******************************************************************************
// Lib�re la m�moire
void Displayer::FreeMemory ( )
{
	freeRenderer ( );
	freeWindow ( );
	freeEngine ( );
}

// Lib�re renderer
void Displayer::freeRenderer ( )
{
	factory->release( font );

	factory->release( camera );

	renderer->finalize();

	factory->release( renderer );
}
	
// Lib�re window
void Displayer::freeWindow ( )
{
	window->hide();

	window->unregisterCloseCallback( onClose );
	window->unregisterKeyDownCallback( onKeyDown );
	window->unregisterKeyUpCallback( onKeyUp );
	window->unregisterMouseMoveCallback( onMouseMove );

	delete window;
}

// Lib�re engine
void Displayer::freeEngine ( )
{
	factory = NULL;

	delete engine;
}



/******************************************************************************
*                 Constructeurs et destructeurs                               *
******************************************************************************
// Constructeur
Displayer::Displayer ( )
: engine( 0 ), factory( 0 ), window( 0 ), camera( 0 ), model( 0 ), font( 0 )
{
}

// Destructeur
Displayer::~Displayer ( )
{
}
*/