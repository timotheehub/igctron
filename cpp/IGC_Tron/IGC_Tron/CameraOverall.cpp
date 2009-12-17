// CameraOverall.h
// Definition de la classe CameraOverall

#include "CameraOverall.h"
#include "Displayer.h"

/******************************************************************************
*                             Mise a jour                                     *
******************************************************************************/
void CameraOverall::Update ( )
{
	AbstractCamera::Update ( );
}

/******************************************************************************
*                    Constructeur et destructeur                              *
******************************************************************************/
CameraOverall::CameraOverall ( )
: AbstractCamera ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Window* window = aDisplayer->GetWindow ( );

	aCamera->setRatio( window->getInnerWidth(), window->getInnerHeight() );
	aCamera->setCenter( 20.0f, 20.0f, 0.0f );
	aCamera->lookAt( -0.1f, -1.0f, 0.0f );
	aCamera->update();
}

CameraOverall::~CameraOverall ( )
{
}
