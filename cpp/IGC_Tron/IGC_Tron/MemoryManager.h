#ifndef __MEMORYMANAGER_H__
#define __MEMORYMANAGER_H__

#include "Globals.h"

// Only for Windows
#ifdef WINDOWS

#include "Lock.h"

#define MEMORY_TAB_SIZE		1024
#define CALLSTACK_SIZE		10

void* operator new( size_t );
void  operator delete( void* );

unsigned long WalkStack( unsigned long callStack[], unsigned long bufferSize );

class MemoryManager
{
public:	
	friend void* operator new( size_t );
	friend void  operator delete( void* );

	static MemoryManager* GetInstance();
	~MemoryManager(void);

	void Start();
	void Stop();	

	unsigned long GetAllocatedMemory()  { return m_TotalAllocated; }

protected:

	// Representing an allocation
	class MemoryWalk
	{
		public:
			void* ptr;		// Allocated pointer
			size_t size;	// Allocated size
			unsigned long callStack[CALLSTACK_SIZE];	// Call stack containing pointers
			
			MemoryWalk* next;
	};

	// Repesenting memory
	class MemoryTab
	{
		public:
			MemoryWalk*	memTop[MEMORY_TAB_SIZE];
	};

	unsigned long m_TotalAllocated;

private:
	MemoryManager(void);

	void* Create( int size, unsigned long callStack[] );
	void  Free( void* ptr );

	void Release();

	unsigned long takeofs( void* ptr );	

	bool m_boInitialized;

	MemoryWalk*	memTop;
	MemoryWalk* memCurrent;
	MemoryWalk* memPtr;
	MemoryWalk* memOld;

	MemoryTab*	memTab;

	int m_nItems;

	CriticalSection cs;
};

#endif // WINDOWS
#endif // __MEMORYMANAGER_H__