
#include "SimpleMutex.h"

SimpleMutex::SimpleMutex ( )
{
#ifdef _WIN32
	InitializeCriticalSection( &mutex );
#else
	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_settype( &mutexattr, PTHREAD_MUTEX_FAST_NP );
	pthread_mutex_init( &mutex, &mutexattr );
	pthread_mutexattr_destroy( &mutexattr );
#endif
}

SimpleMutex::~SimpleMutex ( )
{
#ifdef _WIN32
	DeleteCriticalSection( &mutex );
#else
	pthread_mutex_destroy( &mutex );
#endif
}
