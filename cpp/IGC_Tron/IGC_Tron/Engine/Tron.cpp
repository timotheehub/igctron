
/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include "Engine.h"
#include "W32Window.h"
#include "X11Window.h"
#include "D3DRenderer.h"
#include "D3DCamera.h"
#include "D3DMesh.h"
#include "D3DModel.h"
#include "OGLRenderer.h"
#include "OGLCamera.h"
#include "OGLMesh.h"
#include "OGLModel.h"

#pragma warning (disable : 4996)

/***********************************************************************************/
/** DEBUG                                                                         **/
/***********************************************************************************/

#include "Debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***********************************************************************************/

using namespace IGC;

/***********************************************************************************/
/** VARIABLES GLOBALES                                                            **/
/***********************************************************************************/

const bool DEBUG_KEY_CODE = false;

const float MOUSE_SENSIVITY = 0.01f;
const float MOVE_SPEED = 50.0f;

Engine* engine = NULL;
Window* window = NULL;
Renderer* renderer = NULL;
Camera* camera = NULL;
Model* model = NULL;

bool running;

bool moveForward;
bool moveBackward;
bool strafeLeft;
bool strafeRight;

int lastX, lastY;

/***********************************************************************************/
/** EVENEMENTS                                                                    **/
/***********************************************************************************/

void onClose()
{
	running = false;
}

void onMouseMove( int _keyboardContext, int _mouseContext, int _mouseX, int _mouseY )
{
	if ( renderer == NULL ) return;

	if ( _mouseContext & IWindow::MC_LEFT )
	{
		float dx = MOUSE_SENSIVITY * (float)(_mouseX - lastX);
		float dy = MOUSE_SENSIVITY * (float)(_mouseY - lastY);

		camera->rotate( dx, dy, 0.0f );
	}

	lastX = _mouseX;
	lastY = _mouseY;
}

void onKeyDown( int _keyboardContext, int _keyCode )
{
	if ( DEBUG_KEY_CODE )
		printf( "_keyCode = %d\n", _keyCode );

	if ( _keyCode == 90 )
		moveForward = true;
	else if ( _keyCode == 83 )
		moveBackward = true;
	else if ( _keyCode == 81 )
		strafeLeft = true;
	else if ( _keyCode == 68 )
		strafeRight = true;

	if ( _keyCode == 27 ) running = false;
}

void onKeyUp( int _keyboardContext, int _keyCode )
{
	if ( _keyCode == 90 )
		moveForward = false;
	else if ( _keyCode == 83 )
		moveBackward = false;
	else if ( _keyCode == 81 )
		strafeLeft = false;
	else if ( _keyCode == 68 )
		strafeRight = false;
}

/***********************************************************************************/
/** FONCTIONS                                                                     **/
/***********************************************************************************/

void mainLoop()
{
	double cycleTime = 0;

	running = true;

	while( running )
	{
		renderer->clear( 1.0f, 0.0f, 0.0f, 1.0f );

		camera->bind();

		model->render();

		renderer->update();

		engine->update();

		if ( moveForward )
			camera->moveForward( MOVE_SPEED * (float)engine->getDelta() );

		if ( moveBackward )
			camera->moveBackward( MOVE_SPEED * (float)engine->getDelta() );

		if ( strafeLeft )
			camera->moveLeft( MOVE_SPEED * (float)engine->getDelta() );

		if ( strafeRight )
			camera->moveRight( MOVE_SPEED * (float)engine->getDelta() );

		if ( engine->getTime() > cycleTime )
		{
			static char fpsBuffer[12];
			sprintf( fpsBuffer, "%.3f", engine->getCurrentFramerate() );

			static char avgBuffer[12];
			sprintf( avgBuffer, "%.3f", engine->getAverageFramerate() );

			renderer->clearForeground();

			renderer->insertLabel( string("Tron"), 4, 4 );

			if ( engine->getCurrentFramerate() > 40 )
				renderer->insertLabel( string("FPS : ") + string(fpsBuffer), 4, 32, 0.0f, 1.0f, 0.0f, 1.0f );
			else if ( engine->getCurrentFramerate() > 20 )
				renderer->insertLabel( string("FPS : ") + string(fpsBuffer), 4, 32, 1.0f, 1.0f, 0.0f, 1.0f );
			else
				renderer->insertLabel( string("FPS : ") + string(fpsBuffer), 4, 32, 1.0f, 0.0f, 0.0f, 1.0f );

			if ( engine->getAverageFramerate() > 60 )
				renderer->insertLabel( string("AVG : ") + string(avgBuffer), 4, 48, 0.0f, 1.0f, 0.0f, 1.0f );
			else if ( engine->getAverageFramerate() > 20 )
				renderer->insertLabel( string("AVG : ") + string(avgBuffer), 4, 48, 1.0f, 1.0f, 0.0f, 1.0f );
			else
				renderer->insertLabel( string("AVG : ") + string(avgBuffer), 4, 48, 1.0f, 0.0f, 0.0f, 1.0f );

			cycleTime = engine->getTime() + 1.0;

			debugPrint( "FPS : %.3f\n", engine->getCurrentFramerate() );
		}
	}
}

void initWindow()
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

void freeWindow()
{
	window->hide();

	window->unregisterCloseCallback( onClose );
	window->unregisterKeyDownCallback( onKeyDown );
	window->unregisterKeyUpCallback( onKeyUp );
	window->unregisterMouseMoveCallback( onMouseMove );

	delete window;
}

void initEngine()
{
	engine = new Engine();
}

void freeEngine()
{
	delete engine;
}

void initRenderer()
{
	renderer = new Renderer( engine );

	renderer->disableFullscreen();
	renderer->disableVSync();
	renderer->useHardware();

	camera = new Camera( renderer );

	camera->setRatio( window->getInnerWidth(), window->getInnerHeight() );
	camera->setCenter( -10.0f, 20.0f, 30.0f );
	camera->lookAt( 0.0f, 0.0f, 0.0f );
	camera->update();

	renderer->initialize();
}

void freeRenderer()
{
	renderer->finalize();

	delete renderer;
}

void loadScene()
{
	Mesh* mesh = new Mesh( renderer );

	mesh->createCube();
	mesh->update();

	model = new Model( renderer );
	model->setMesh( mesh );
}

void unloadScene()
{
	Mesh* mesh = (Mesh*)model->getMesh();

	if ( mesh )
		delete mesh;

	if ( model )
		delete model;
}

/***********************************************************************************/
/** POINT D'ENTREE                                                                **/
/***********************************************************************************/

int main( int argc, char **argv )
{
	initEngine();

	initWindow();

	initRenderer();

	loadScene();

	mainLoop();

	unloadScene();

	freeRenderer();

	freeWindow();

	freeEngine();

	return 0;
}
