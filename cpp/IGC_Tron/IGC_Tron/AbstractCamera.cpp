// AbstractCamera.h
// Definition de la classe AbstractCamera

#include "AbstractCamera.h"
#include "Displayer.h"

/******************************************************************************
*                                Mise à jour                                  *
******************************************************************************/
void AbstractCamera::UpdateGraphics ( )
{
	aCamera->bind();
}

void AbstractCamera::Update ( double )
{
}

/******************************************************************************
*                      Initialisation et destruction                          *
******************************************************************************/
void AbstractCamera::Init ( )
{
	// Pas de gestion de souris et de touches par défaut.
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
}
