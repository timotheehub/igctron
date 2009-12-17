/*
 * CartesianVector.h
 *
 *  Created on: 3 déc. 2009
 *      Author: fenrhil
 */

#ifndef CARTESIANVECTOR_H_
#define CARTESIANVECTOR_H_

namespace Utils
{

struct CartesianVector
{
	typedef double CoordType;

	CoordType x, y, z;

	CartesianVector& operator +=(const CartesianVector& c)
	{
		x += c.x;
		y += c.y;
		z += c.z;
		return *this;
	}

	CartesianVector& operator -=(const CartesianVector& c)
	{
		x -= c.x;
		y -= c.y;
		z -= c.z;
		return *this;
	}

	CartesianVector& operator *=(CoordType c)
	{
		x *= c;
		y *= c;
		z *= c;
		return *this;
	}

	CartesianVector& operator /=(CoordType c)
	{
		x /= c;
		y /= c;
		z /= c;
		return *this;
	}

	CartesianVector(CoordType xi, CoordType yi, CoordType zi) :
		x(xi), y(yi), z(zi)
	{
	}

	CartesianVector() :
		x(0), y(0), z(0)
	{

	}
};

inline CartesianVector operator +(const CartesianVector& c1, const CartesianVector& c2)
{
	CartesianVector res(c1);
	res += c2;
	return res;
}

inline CartesianVector operator *(CartesianVector::CoordType d, const CartesianVector& c)
{
	CartesianVector res(c);
	res *= d;
	return res;
}

inline CartesianVector operator *(const CartesianVector& c, CartesianVector::CoordType d)
{
	return c * d;
}

} // namespace Utils

#endif /* CARTESIANVECTOR_H_ */