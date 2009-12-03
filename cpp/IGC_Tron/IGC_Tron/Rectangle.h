/*
 * Rectangle.h
 *
 *  Created on: 3 déc. 2009
 *      Author: fenrhil
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <cmath>
#include "CartesianVector.h"

namespace Utils
{

struct Rectangle
{
	typedef CartesianVector::CoordType CoordType;

	bool IsInCollision(const CartesianVector& c1, const CartesianVector& c2) const
	// Retourne vrai si le rectangle (ou sa surface) croise le segment [c1,c2].
	// c1 et c2 seront considérés comme alignés.
	{
		if (fabs(c1.x - c2.x) < fabs(c1.z - c2.z))
		{
			// Alignés selon x.

			if (c1.x < xMin || xMax < c1.x)
			{
				return false;
			}
			else
			{
				// xMin.x <= c1.x <= xMax.x
				CoordType cZMin, cZMax;
				if (c1.z < c2.z)
				{
					cZMin = c1.z;
					cZMax = c2.z;
				}
				else
				{
					cZMin = c2.z;
					cZMax = c1.z;
				}

				return (cZMin < zMax && zMin < cZMax);
			}
		}
		else
		{
			// Alignés selon z.

			if (c1.z < zMin || zMax < c1.z)
			{
				return false;
			}
			else
			{
				// zMin.z < c1.z < zMax.z
				CoordType cXMin, cXMax;
				if (c1.x < c2.x)
				{
					cXMin = c1.x;
					cXMax = c2.x;
				}
				else
				{
					cXMin = c2.x;
					cXMax = c1.x;
				}

				return (cXMin < xMax && xMin < cXMax);
			}
		}
	}

	bool IsInCollision(const Rectangle& r) const
	{
		return !(zMax < r.zMin || r.zMax < zMin || xMax
				< r.xMin || r.xMax < xMin);
	}

	Rectangle(const CartesianVector& position, const CartesianVector& direction,
			CoordType lengthAhead, CoordType lengthBack, CoordType widthLeft,
			CoordType widthRight) :
		xMin(position.x), xMax(position.x), zMin(position.z), zMax(position.z)
	{
		// On a forcément direction.x == 0 xor direction.z == 0
		// Et position.x >= 0 et position.z >= 0
		if (direction.x < 0)
		{
			xMin -= lengthAhead;
			xMax += lengthBack;
			zMin -= widthRight;
			zMax += widthLeft;
		}
		else if (direction.x > 0)
		{
			xMin -= lengthBack;
			xMax += lengthAhead;
			zMin -= widthLeft;
			zMax += widthRight;
		}
		else if (direction.z < 0)
		{
			zMin -= lengthAhead;
			zMax += lengthBack;
			xMin -= widthLeft;
			xMax += widthRight;
		}
		else
		{
			zMin -= lengthBack;
			zMax += lengthAhead;
			xMin -= widthRight;
			xMax += widthLeft;
		}
	}

	// On modélise le rectangle par une croix dont les lignes sont
	// perpendiculaires aux côtés du rectangles.
	// Ex :
	// ---------------------
	// |     |             |
	// |-----+-------------|
	// |     |             |
	// ---------------------
	CoordType xMin; // Point le plus proche de l'axe z
	CoordType xMax; // Point le plus éloigné de l'axe z
	CoordType zMin; // Point le plus proche de l'axe x
	CoordType zMax; // Point le plus éloigné de l'axe x

private:
};

} // namespace Utils

#endif /* RECTANGLE_H_ */
