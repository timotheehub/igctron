/**************************************************************************/
/* This file is part of IGC Tron                                          */
/* (c) IGC Software 2009 - 2010                                           */
/* Author : Pierre-Yves GATOUILLAT                                        */
/**************************************************************************/
/* This program is free software: you can redistribute it and/or modify   */
/* it under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                    */
/*                                                                        */
/* This program is distributed in the hope that it will be useful,        */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/* GNU General Public License for more details.                           */
/*                                                                        */
/* You should have received a copy of the GNU General Public License      */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>.  */
/**************************************************************************/

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

#include "Engine.h"
#include "Factory.h"
#include "W32Window.h"
#include "X11Window.h"
#include "D3DRenderer.h"
#include "D3DCamera.h"
#include "D3DMesh.h"
#include "D3DModel.h"
#include "D3DFont.h"
#include "D3DTexture.h"
#include "OGLRenderer.h"
#include "OGLCamera.h"
#include "OGLMesh.h"
#include "OGLModel.h"
#include "OGLFont.h"
#include "OGLTexture.h"

#ifdef _WIN32
	#pragma warning (disable : 4996)
#endif

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

IGC::Engine* engine = NULL;
IGC::Factory* factory = NULL;
IGC::Window* window = NULL;
IGC::Renderer* renderer = NULL;
IGC::Camera* camera = NULL;
IGC::Model* model = NULL;
IGC::Font* font = NULL;
IGC::Texture* texture = NULL;
IGC::Texture* image = NULL;

bool running;

bool moveForward;
bool moveBackward;
bool strafeLeft;
bool strafeRight;
#ifdef _WIN32
	int MoveForwardKeyCode = 90;
	int MoveBackwardKeyCode = 83;
	int StrafeLeftKeyCode = 81;
	int StrafeRightKeyCode = 68;
	int QuitKeyCode = 27;
#else
	int MoveForwardKeyCode = 111;
	int MoveBackwardKeyCode = 116;
	int StrafeLeftKeyCode = 113;
	int StrafeRightKeyCode = 114;
	int QuitKeyCode = 9;
#endif

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
		printf( "DOWN : _keyCode = %d\n", _keyCode );

	if ( _keyCode == MoveForwardKeyCode )
		moveForward = true;
	else if ( _keyCode == MoveBackwardKeyCode )
		moveBackward = true;
	else if ( _keyCode == StrafeLeftKeyCode )
		strafeLeft = true;
	else if ( _keyCode == StrafeRightKeyCode )
		strafeRight = true;

	if ( _keyCode == QuitKeyCode ) running = false;
}

void onKeyUp( int _keyboardContext, int _keyCode )
{
	if ( DEBUG_KEY_CODE )
		printf( "UP : _keyCode = %d\n", _keyCode );

	if ( _keyCode == MoveForwardKeyCode )
		moveForward = false;
	else if ( _keyCode == MoveBackwardKeyCode )
		moveBackward = false;
	else if ( _keyCode == StrafeLeftKeyCode )
		strafeLeft = false;
	else if ( _keyCode == StrafeRightKeyCode )
		strafeRight = false;
}

/***********************************************************************************/
/** FONCTIONS                                                                     **/
/***********************************************************************************/

void mainLoop()
{
	double cycleTime = 0;

	static char fpsBuffer[20];
	static char avgBuffer[20];

	running = true;

	while( running )
	{
		renderer->clear( 1.0f, 0.2f, 0.2f, 1.0f );

		camera->bind();

		texture->bind();

		renderer->setTransparency( false );

		model->render();

		{
			font->bind();

			int x = renderer->toPointX( 0.01f );
			int y = renderer->toPointY( 0.01f );

			renderer->drawText( "Tron", x, y, 1.0f, 1.0f, 1.0f, 1.0f );

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


		{
			image->bind();
			
			renderer->setTransparency( true );

			int x0 = renderer->toPointX( 0.01f );
			int y0 = renderer->toPointY( 0.63f );
			int x1 = renderer->toPointX( 0.27f );
			int y1 = renderer->toPointY( 0.79f );

			renderer->drawImage( x0, y0, x1, y1, 0.0f, 0.0f, 1.0f, 1.0f, 0.4f, 1.0f, 0.4f, 1.0f );
		}

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
			sprintf( fpsBuffer, "FPS : %.3f", engine->getCurrentFramerate() );
			sprintf( avgBuffer, "AVG : %.3f", engine->getAverageFramerate() );

			cycleTime = engine->getTime() + 1.0;
		}
	}
}

void initWindow()
{
	window = factory->acquire( (IGC::Window*)NULL, "toto" );

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

	factory->release( window );
}

void initEngine()
{
	engine = new Engine();

	factory = engine->getFactory();
}

void freeEngine()
{
	factory = NULL;

	delete engine;
}

void initRenderer()
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

void freeRenderer()
{
	factory->release( font );

	factory->release( camera );

	renderer->finalize();

	factory->release( renderer );
}

void loadScene()
{
	model = factory->acquire( (IGC::Model*)NULL );

	model->import( "ship.3ds" );
	model->shrink( 8.0f, 8.0f, 8.0f );
	//model->rotate( PI * 0.5f, PI * 1.0f, 0.0f );
	model->rotate(0,0,PI);
	model->setSize(0.125,0.25,0.125);
	model->move( 50.0f, 0.0f, -50.0f );

	texture = factory->acquire( (IGC::Texture*)NULL );

	texture->import( "warp.png" );

	image = factory->acquire( (IGC::Texture*)NULL );

	image->import( "logo.png" );
}

void unloadScene()
{
	factory->release( image );
	factory->release( texture );

	factory->release( model );
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

	debugMemoryLeaks();

	return 0;
}
