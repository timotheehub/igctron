/****************************************************
* Class : CriticalSection   						*
* Author : Sébastien M.                             *
* Handles threads critical sections.			    *
****************************************************/

#ifndef __CRITICALSECTION_H__
#define __CRITICALSECTION_H__

#include "Globals.h"

#ifdef WINDOWS
#include <windows.h>
#endif
#ifdef UNIX
#include <unistd.h>
#include <process.h>
#endif

class CriticalSection
{
public:

	/////////////////////////////////////////////////
	// Constructor
	CriticalSection(void) :
	  m_nThreadId( 0 ), m_nLockCount( 0 )
	{		
	}

	/////////////////////////////////////////////////
	// Destructor
	~CriticalSection(void)
	{
	}

	/////////////////////////////////////////////////
	// Enter in a critical section
	void Enter()
	{
		long nThreadId;

#if defined(WINDOWS)		
		nThreadId = GetCurrentThreadId();
#elif defined(UNIX)
		nThreadId = getpid();
#endif
		
		if( m_nThreadId == nThreadId )
			m_nLockCount++;
		else
		{
			while( true )
			{
				if( Lock( nThreadId ) ) break; 
				
			}
		}
	}

	/////////////////////////////////////////////////
	// Leave a critical section
    void Leave()
	{
		long nThreadId;

#if defined(WINDOWS)
		nThreadId = GetCurrentThreadId();
#elif defined(UNIX)
		nThreadId = getpid();
#endif

		if( m_nThreadId == nThreadId ) 
		{
			if( m_nLockCount > 1 )
				m_nLockCount--;
			else
			{
				m_nLockCount = 0;

#if defined(WINDOWS)
		InterlockedExchange( (LONG*) &m_nThreadId, 0 );
#elif defined(UNIX)
		m_nThreadId = 0; // Non-atomic... How can I do ?
#endif
				
			}
		}
	}

	/////////////////////////////////////////////////
	// Try to enter a critical section
	// Return true if succeed, false otherwize
    bool Try()
	{
		long nThreadId;

#if defined(WINDOWS)		
		nThreadId = GetCurrentThreadId();
#elif defined(UNIX)
		nThreadId = getpid();
#endif

		if( m_nThreadId == nThreadId ) 
		{
			m_nLockCount++;
			return true;
		}

		return Lock( nThreadId );	
	}	

private:

	unsigned long m_nLockCount;
    unsigned long m_nThreadId;    

	/////////////////////////////////////////////////
	// Lock thread
	bool Lock( const long nThreadId )
	{	
#if defined(WINDOWS)
		if( InterlockedCompareExchange( (LONG*) &m_nThreadId, (LONG) nThreadId, 0 ) == 0 )
		{
			m_nLockCount = 1;
			return true;
		}
#elif defined(UNIX)		
		// Non-atomic way = bad way
		if( m_nThreadId == 0 )
		{
			m_nThreadId = nThreadId;
			m_nLockCount = 1;
			return true;
		}
#endif

		return false;
	}
};

#endif // __CRITICALSECTION_H__