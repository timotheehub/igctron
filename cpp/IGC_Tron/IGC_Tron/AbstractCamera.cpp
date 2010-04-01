// AbstractCamera.h
// Definition de la classe AbstractCamera

#include "AbstractCamera.h"
#include "Displayer.h"

/******************************************************************************
*                                Mise � jour                                  *
******************************************************************************/
void AbstractCamera::Update ( )
{
	aCamera->bind();
}

/******************************************************************************
*                      Initialisation et destruction                          *
******************************************************************************/
void AbstractCamera::Init ( )
{
	// Pas de gestion de souris et de touches par d�faut.
}

void AbstractCamera::Free ( )
{
}

/******************************************************************************
*                     Constructeur et destructeur                             *
******************************************************************************/
AbstractCamera::AbstractCamera ( )
{
}

AbstractCamera::~AbstractCamera ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	Factory* aFactory = aDisplayer->GetFactory();
	aCamera = aFactory->acquire( (IGC::Camera*)NULL, "camera_overall" );
	aFactory->release( aCamera );
	aFactory->release( aCamera );
}