// CameraOverall.h
// Definition de la classe CameraOverall

#include "CameraOverall.h"
#include "Displayer.h"

/******************************************************************************
*                    Constructeur et destructeur                              *
******************************************************************************/
CameraOverall::CameraOverall ( )
: AbstractCamera ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	Factory* aFactory = aDisplayer->GetFactory();
	aCamera = aFactory->acquire( (IGC::Camera*)NULL );
	IGC::Window* window = aDisplayer->GetWindow ( );

	aCamera->setRatio( window->getInnerWidth(), window->getInnerHeight() );
	aCamera->setCenter( 30.0f, 20.0f, 15.0f );
	aCamera->lookAt( -10.1f, -1.0f, 15.0f );
	aCamera->update();
}

CameraOverall::~CameraOverall ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	Factory* aFactory = aDisplayer->GetFactory();
	aFactory->release ( aCamera );
}
