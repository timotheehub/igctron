#include <iostream>
#include "MemoryManager.h"

#undef new

/////////////////////////////////////////////////
// Redefinition of the new operator
void* operator new( size_t size )
{
	if( MemoryManager::GetInstance()->m_boInitialized == false )
		return malloc( size );

   unsigned long callStack[CALLSTACK_SIZE];
   unsigned long levels = WalkStack( callStack, CALLSTACK_SIZE );

   Lock lock( &MemoryManager::GetInstance()->cs );
   return MemoryManager::GetInstance()->Create( size, callStack );
}

/////////////////////////////////////////////////
// Redefinition of the delete operator
void operator delete( void* ptr )
{
	if( MemoryManager::GetInstance()->m_boInitialized == false )
	{
		free( ptr );
		return;
	}
   
	Lock lock( &MemoryManager::GetInstance()->cs );
	MemoryManager::GetInstance()->Free( ptr );	
}

/////////////////////////////////////////////////
// Returns all the previous call addresses from this thread
unsigned long WalkStack( unsigned long callStack[], unsigned long bufferSize )
{
#if _M_IX86 && defined(WINDOWS)

    unsigned long rEbp;
    __asm{
        mov rEbp, ebp
    };
   
    unsigned long currentLevel = 0;
    while( rEbp != 0 )
	{
        if( currentLevel > bufferSize )
		{
            return currentLevel;
        }
        
        // Store calling address from this ebp
        callStack[currentLevel] = *(unsigned long*)( rEbp + 4 );
        
        // Move to next stack frame
        rEbp = *(unsigned long*)rEbp;

        currentLevel++;
    }
    return currentLevel;
#else
    return 0;
#endif
}

/////////////////////////////////////////////////
// Return the only instance of the class
MemoryManager* MemoryManager::GetInstance()
{
	static MemoryManager m_pInstance;
	return &m_pInstance;
}

/////////////////////////////////////////////////
// Constructor
MemoryManager::MemoryManager(void) :
	memTop( NULL ), memCurrent( NULL ), memOld( NULL ), memPtr( NULL ), m_TotalAllocated( 0 ),
    m_nItems( 0 ), m_boInitialized( false )
{
	// Tab creation
	memTab = (MemoryTab*) malloc( sizeof( MemoryTab ) );

#if defined(WINDOWS)	
	ZeroMemory( memTab, sizeof( MemoryTab ) );
#elif defined(UNIX)
	memset( memTab, 0, sizeof( MemoryTab ) );
#endif
}

/////////////////////////////////////////////////
// Destructor
MemoryManager::~MemoryManager(void)
{
	Release();
	
	free( memTab );
}

/////////////////////////////////////////////////
// Start Memory Manager
void MemoryManager::Start()
{
	if( memTab != NULL )
		m_boInitialized = true;
}

/////////////////////////////////////////////////
// Stop Memory Manager
void MemoryManager::Stop()
{
	if( memTab != NULL )
	{
		Release();
	}
}

/////////////////////////////////////////////////
// Release every objects
void MemoryManager::Release()
{
	m_boInitialized = false;
	
	int j = 0;
	
	unsigned long TotalLeak = 0;
	for( int i = 0; i < MEMORY_TAB_SIZE; ++i )	
	{
		memPtr = memTab->memTop[i];
													
		while( memPtr != NULL )
		{			
			memCurrent = memPtr->next;

			if( memPtr->ptr != NULL )
			{				
				printf( "\nMemory Leak @ 0x%x (size %d)\n\tCall Stack: ", memPtr->ptr, memPtr->size );
				j++;

                int n = 1;
                while( n < CALLSTACK_SIZE && memPtr->callStack[n] != NULL )
				{
					printf( n == 1 ? "0x%x" : ", 0x%x", memPtr->callStack[n] );                    
                    n++;
                }
				
                TotalLeak += memPtr->size;								
			}

			memPtr = memCurrent;
		}
	}
      
   if( j != 0 )
	   printf( "\n\nNumber of leaks: %d\nSize of leaks: %ld\nLeaks average: %ld\n", j, TotalLeak, TotalLeak/j );   
}

/////////////////////////////////////////////////
// Getting a placement for this pointer (generate a kind of hash)
unsigned long MemoryManager::takeofs( void* ptr )
{
	unsigned long addr = ((unsigned long) ptr & 0xffff) >> 6;
	return addr;
}

/////////////////////////////////////////////////
// Create a new entry in the tab and push the new pointer
void* MemoryManager::Create( int size, unsigned long callStack[] )
{
	if( memTab == NULL )
		return NULL;
  
	// Memory allocation and get a kind of hash
    void *ptr = malloc( size );
	unsigned long addr = takeofs( ptr );

	// If there's already something here
	if( memTab->memTop[addr] != NULL )
	{
		// Try to get a free one
		memCurrent = memTab->memTop[addr];

		while( memCurrent->next != NULL )
			memCurrent = memCurrent->next;

		// Creates the new pointer
		memCurrent->next = (MemoryWalk*) malloc( sizeof(MemoryWalk) );

#if defined(WINDOWS)
		ZeroMemory( memCurrent->next, sizeof(MemoryWalk) );
#elif defined(UNIX)
		memset( memCurrent->next, 0, sizeof(MemoryWalk) );
#endif

		memPtr = memCurrent->next;
	}
	else
	{
		// Creates directly the new pointer
		memTab->memTop[addr] = (MemoryWalk*) malloc( sizeof(MemoryWalk) );

#if defined(WINDOWS)
		ZeroMemory( memTab->memTop[addr], sizeof(MemoryWalk) );
#elif defined(UNIX)
		memset( (memTab->memTop[addr], 0, sizeof(MemoryWalk) );
#endif
		
		memCurrent = memTab->memTop[addr];
		memPtr = memCurrent;
	}
  
	// Set up pointer information
	memPtr->ptr       = ptr;
  	m_TotalAllocated += size;
	memPtr->size      = size;

    memcpy( memPtr->callStack, callStack, sizeof(memPtr->callStack) );

	memPtr->next = NULL;	
	m_nItems++;
	
	return ptr;
}

/////////////////////////////////////////////////
// Free a pointer
void MemoryManager::Free( void* ptr )
{
	MemoryWalk* memPrev = NULL;
	MemoryWalk* memNext = NULL;

	unsigned long addr = takeofs( ptr );	

   if( memTab == NULL )
   {
   		free( ptr );	
		return;
   }
	
	// Get the entry
	memPtr = memTab->memTop[addr];
	// If the pointer don't match, free it
    if( memPtr == NULL )
	{
   		free(ptr);	
		return;
	}

	// Seek for our pointer
	while( memPtr->next || memPtr->ptr == ptr )
	{
		// If the pointer matches
		if( memPtr->ptr == ptr )
		{
			// Reset him and let's kick him from the list
			memPtr->ptr = NULL;
      		m_TotalAllocated -= memPtr->size;
			memPtr->size = 0;
			memNext = memPtr->next;

			if( memPrev != NULL ) 
				memPrev->next = memNext;
			else
				memTab->memTop[addr] = memNext;

			free( memPtr );			
			m_nItems--;

			break;
		}

		memPrev = memPtr;
		memPtr  = memPtr->next;
	}

	free( ptr );	
}