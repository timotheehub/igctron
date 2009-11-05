// Singleton.cpp
// Définition de la classe Singleton

#include "Singleton.h"

template <typename T>
T *Singleton<T>::theSingleton = 0;