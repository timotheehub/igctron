/*
 * Wall.cpp
 *
 *  Created on: 3 déc. 2009
 *      Author: fenrhil
 */

using namespace std;
#include <vector>
#include "Wall.h"
#include "Globals.h"
using namespace Utils;

void Wall::SetLastVertex(const CartesianVector& value)
{
	*vertexes.rend() = value;
}

void Wall::NewVertex()
{
	vertexes.push_back(*vertexes.rend());
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
