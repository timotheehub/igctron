// Globals.h
// D�finition de constantes

#ifndef __GLOBALS_H__
#define __GLOBALS_H__ 

#include "CartesianVector.h"
#include "Rectangle.h"
#include "Common.h"

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
const int F1 = 112;
const int F2 = 113;
#else
const int ENTER = 36;
const int ESCAPE = 9;
const int UP = 111;
const int LEFT = 113;
const int RIGHT = 114;
const int DOWN = 116;
const int Z = 25;
const int S = 39;
const int Q = 38;
const int D = 40;
const int F1 = 67;
const int F2 = 68;
#endif
}

const float4 COLOR_WHITE = make_float4(1.0f, 1.0f, 1.0f, 1.0f);

#endif // __GLOBALS_H__
