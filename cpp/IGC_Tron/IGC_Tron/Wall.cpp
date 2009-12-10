/*
 * Wall.cpp
 *
 *  Created on: 3 déc. 2009
 *      Author: fenrhil
 */

#include <vector>
#include "Wall.h"
#include "Globals.h"
#include "Displayer.h"
using namespace std;
using namespace Utils;

void Wall::Init(const CartesianVector& origin)
{
	vertexes.assign(2, origin);
}

void Wall::SetLastVertex(const CartesianVector& value)
{
	*vertexes.rbegin() = value;
}

void Wall::NewVertex()
{
	vertexes.push_back(*vertexes.rbegin());

	xDirection = !xDirection;
	models.push_back(factory->aquire((IGC::Model*)NULL));
	if (xDirection)
	{
		models.back()->Clone(Displayer::GetInstance()->GetFactory()->acquire ( (IGC::Model*)NULL, "model_wallX" ));
	}
	else
	{
		models.back()->Clone(Displayer::GetInstance()->GetFactory()->acquire ( (IGC::Model*)NULL, "model_wallZ" ));
	}
}

void Wall::Draw() const
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Renderer *renderer = aDisplayer->GetRenderer ( );
	IGC::Factory *factory = aDisplayer->GetFactory ( );

	IGC::Model* model;
	IGC::Texture* texture = factory->acquire ( (IGC::Texture*)NULL, "logo_orange" );
	texture->bind ( );
	renderer->setTransparency( false );

	vector<CartesianVector>::const_iterator it1, it2;

	for (it1 = vertexes.begin(), it2 = it1 + 1; it2 != vertexes.end(); it1 = it2, ++it2)
	{
		if (fabs(it1->x - it2->x) > fabs(it1->z - it2->z))
		{
			model->grow( fabs(it1->x - it2->x), 1.0f, 1.0f );
		}
		else
		{
			model->grow( 1.0f, 1.0f, fabs(it1->z - it2->z) );	
		}
		model->setCenter ( fabs(it1->x + it2->x)/2 - 10, 0.5f, fabs(it1->z + it2->z)/2 - 15);
		model->render();
	}
}

bool Wall::IsInCollision(const Utils::Rectangle& object) const
{
	vector<CartesianVector>::const_iterator it1, it2;

	for (it1 = vertexes.begin(), it2 = it1 + 1; it2 != vertexes.end()
			&& !object.IsInCollision(*it1, *it2); it1 = it2, ++it2)
	{
		// Bloc vide
	}

	return it2 != vertexes.end();
}

Wall::Wall(const CartesianVector& origin, const CartesianVector& direction) :
	vertexes(2, origin), models(1,0), xDirection(fabs(direction.x) > fabs(direction.z))
{

}

