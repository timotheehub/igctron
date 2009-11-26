// Globals.h
// D�finition de constantes

#ifndef __GLOBALS_H__
#define __GLOBALS_H__ 

#define MAJOR_VERSION "1"
#define MINOR_VERSION "00"

#define WINDOWS

namespace KeyCodes
{
#ifdef _WIN32
const int ENTER = 13;
const int ESCAPE = 27;
const int UP = 38;
const int LEFT = 37;
const int RIGHT = 39;
const int DOWN = 40;
#else
const int ENTER = 36;
const int ESCAPE = 9;
const int UP = 111;
const int LEFT = 113;
const int RIGHT = 114;
const int DOWN = 116;
#endif
}

namespace Utils
{
struct CartesianVector
{
	double x, y, z;

	inline CartesianVector& operator +=(const CartesianVector& c)
	{
		x += c.x;
		y += c.y;
		z += c.z;
		return *this;
	}

	inline CartesianVector& operator -=(const CartesianVector& c)
	{
		x -= c.x;
		y -= c.y;
		z -= c.z;
		return *this;
	}

	inline CartesianVector& operator *=(double c)
	{
		x *= c;
		y *= c;
		z *= c;
		return *this;
	}

	inline CartesianVector& operator /=(double c)
	{
		x /= c;
		y /= c;
		z /= c;
		return *this;
	}

	CartesianVector(double xi, double yi, double zi) :
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

inline CartesianVector operator *(double d, const CartesianVector& c)
{
	CartesianVector res(c);
	res *= d;
	return res;
}

inline CartesianVector operator *(const CartesianVector& c, double d)
{
	return c * d;
}
}

#endif // __GLOBALS_H__
