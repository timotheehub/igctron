/*
 * Wall.cpp
 *
 *  Created on: 3 déc. 2009
 *      Author: fenrhil
 */

#include <vector>
#include "Wall.h"
#include "Globals.h"
using namespace std;
using namespace Utils;

void Wall::SetLastVertex(const CartesianVector& value)
{
	*vertexes.rbegin() = value;
}

void Wall::NewVertex()
{
	vertexes.push_back(*vertexes.rbegin());
}

void Wall::Draw() const
{
	/*
	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Renderer *renderer = aDisplayer->GetRenderer ( );
	IGC::Factory *factory = aDisplayer->GetFactory ( );

	IGC::Model* model;
	switch ( playerNumber )
	{
		case 0: model = factory->acquire( (IGC::Model*)NULL, "model_ship1" );
			break;
		case 1: model = factory->acquire( (IGC::Model*)NULL, "model_ship2" );
			break;
		case 2: model = factory->acquire( (IGC::Model*)NULL, "model_ship3" );
			break;
		case 3: model = factory->acquire( (IGC::Model*)NULL, "model_ship4" );
			break;
		default:
			model = factory->acquire( (IGC::Model*)NULL, "model_ship1" );
			break;
	}
	model->setCenter ( position.x - 15, position.y + 1, position.z - 10 );
	if ( abs ( speed.x ) > abs ( speed.z ) )
	{
		if ( speed.x < 0 )
			model->setAngle ( PI / 2, PI, 0 );
		else
			model->setAngle ( PI / 2, 0, 0 );
	}
	else
	{
		if ( speed.z < 0 )
			model->setAngle ( PI / 2, PI / 2, 0 );
		else
			model->setAngle ( PI / 2, 3*PI / 2, 0 );
	}



	IGC::Texture* texture = factory->acquire( (IGC::Texture*)NULL, "back_screen_menu" );
	texture->bind();
	renderer->setTransparency( false );
	model->render();*/
}

bool Wall::IsInCollision(const Rectangle& object) const
{
	vector<CartesianVector>::const_iterator it1, it2;

	for (it1 = vertexes.begin(), it2 = it1 + 1; it2 != vertexes.end()
			&& !object.IsInCollision(*it1, *it2); it1 = it2, ++it2)
	{
		// Bloc vide
	}

	return it2 != vertexes.end();
}

Wall::Wall(const CartesianVector& origin) :
	vertexes(2, origin)
{

}
