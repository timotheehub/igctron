
#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

class SimpleMutex
{

private:

#ifdef _WIN32
	CRITICAL_SECTION mutex;
#else
	pthread_mutex_t mutex;
#endif

public:

	SimpleMutex ( ) ;
	~SimpleMutex ( ) ;

	inline void AcquireLock ( ) ;
	inline void ReleaseLock ( ) ;

};

inline void SimpleMutex::AcquireLock ( )
{
#ifdef _WIN32
	EnterCriticalSection( &mutex );
#else
	pthread_mutex_lock( &mutex );
#endif
}

inline void SimpleMutex::ReleaseLock ( )
{
#ifdef _WIN32
	LeaveCriticalSection( &mutex );
#else
	pthread_mutex_unlock( &mutex );
#endif
}
