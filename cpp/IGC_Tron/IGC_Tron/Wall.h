/*
 * Wall.h
 *
 *  Created on: 26 nov. 2009
 *      Author: fenrhil
 */

#ifndef WALL_H_
#define WALL_H_

#include <vector>
#include "Globals.h"

class Wall
{
public:
	void SetLastVertex(const Utils::CartesianVector& value);

	void NewVertex();

	bool IsInCollision(const Utils::Rectangle& object) const;

	Wall (const Utils::CartesianVector& origin);

private:
	std::vector<Utils::CartesianVector> vertexes;
};

#endif /* WALL_H_ */
