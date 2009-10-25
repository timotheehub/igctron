/****************************************************
* Class : Lock   									*
* Author : Sébastien M.                             *
* Handles threads critical sections.			    *
****************************************************/

#ifndef __LOCK_H__
#define __LOCK_H__

#include "Globals.h"
#include "CriticalSection.h"

class Lock
{
private:
	CriticalSection* m_pCS;

public:

	/////////////////////////////////////////////////
	// Constructor
	// Entering the current thread in a critical section
	Lock( CriticalSection* pCS ) :
	  m_pCS( pCS )
	{
		if( m_pCS != NULL )
			m_pCS->Enter();
	}

    /////////////////////////////////////////////////
	// Destructor
    // Leaving the critical section
	~Lock(void)
	{
		if( m_pCS != NULL )
			m_pCS->Leave();
	}
};

#endif // __LOCK_H__