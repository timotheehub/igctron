// Globals.h
// D�finition de constantes

#ifndef __GLOBALS_H__
#define __GLOBALS_H__ 

#include "CartesianVector.h"
#include "Rectangle.h"

namespace KeyCodes
{
#ifdef _WIN32
const int ENTER = 13;
const int ESCAPE = 27;
const int UP = 38;
const int LEFT = 37;
const int RIGHT = 39;
const int DOWN = 40;
const int Z = 90;
const int S = 83;
const int Q = 81;
const int D = 68;
#else
const int ENTER = 36;
const int ESCAPE = 9;
const int UP = 111;
const int LEFT = 113;
const int RIGHT = 114;
const int DOWN = 116;
const int Z = 111;
const int S = 116;
const int Q = 113;
const int D = 114;
#endif
}

#endif // __GLOBALS_H__
