// Displayer.h
// D�claration de la classe Displayer

#include "Displayer.h"
using namespace IGC;

bool Displayer::running = true;

void Displayer::OnClose ( )
{
	running = false;
}

bool Displayer::GetRunning ( )
{
	return running;
}
	
void Displayer::SetRunning ( bool isRunning )
{
	running = isRunning;
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
	model = factory->acquire( (IGC::Model*)NULL );

	model->import( "ship.3ds" );
	model->shrink( 8.0f, 8.0f, 8.0f );
	model->rotate( PI * 0.5f, PI * 1.0f, 0.0f );
	model->move( 0.0f, 0.0f, -50.0f );

	texture = factory->acquire( (IGC::Texture*)NULL );
	texture->import( "warp.png" );
}

void Displayer::UnloadScene()
{
	factory->release( texture );
	factory->release( model );
}



/******************************************************************************
*                   Initialisation pour l'�cran                               *
******************************************************************************/
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
	window = new IGC::Window( engine );

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

	camera = factory->acquire( (IGC::Camera*)NULL );
	camera->setRatio( window->getInnerWidth(), window->getInnerHeight() );
	camera->setCenter( 0.0f, 30.0f, 10.0f );
	camera->lookAt( 0.0f, 0.0f, -50.0f );
	camera->update();

	font = factory->acquire( (IGC::Font*)NULL );
	font->setName( "Verdana" );
	font->setSize( 12 );
	font->setBold( true );
	font->setItalic( false );
	font->update();
}



/******************************************************************************
*              Met � jour la partie la partie graphique                       *
******************************************************************************/
// Rafra�chit graphiquement
void Displayer::UpdateGraphics ( )
{
	double cycleTime = 0;

	static char fpsBuffer[20];
	static char avgBuffer[20];

	renderer->clear( 1.0f, 0.0f, 0.0f, 1.0f );

	camera->bind();

	texture->bind();

	renderer->setTransparency( false );

	model->render();

	{
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
	}

	renderer->update();

	engine->update();

	if ( engine->getTime() > cycleTime )
	{
		sprintf( fpsBuffer, "fps : %.3f", engine->getCurrentFramerate() );
		sprintf( avgBuffer, "avg : %.3f", engine->getAverageFramerate() );

		cycleTime = engine->getTime() + 1.0;
	}
}



/******************************************************************************
*                        Lib�re la m�moire                                    *
******************************************************************************/
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
	window->unregisterCloseCallback( OnClose );

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
******************************************************************************/
// Constructeur
Displayer::Displayer ( )
: engine( 0 ), factory( 0 ), window( 0 ), renderer( 0 ), camera( 0 ),
		model( 0 ), font( 0 ), texture( 0 )
{
}

// Destructeur
Displayer::~Displayer ( )
{
}
