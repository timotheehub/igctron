/****************************************************
* Class : Graph     								*
* Author : Sébastien M.                             *
* Represents a graph with his nodes.                *
****************************************************/

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "GraphNode.h"
#include "GraphIterator.h"

template < class T >
class Graph
{
public:
	// Constructor
	Graph( GraphNode<T>* pRoot = NULL ) :
	  m_pRoot( pRoot )
	{
	}

	// Destructor
	~Graph(void)
	{
		if( m_pRoot != NULL )
			delete m_pRoot;
	}
	
	// Returns root node
	GraphNode<T>* GetRootNode()
	{ 
		return m_pRoot;
	};

	// Change the root node
	void SetRootNode( GraphNode<T>* pRoot )
	{		
		if( m_pRoot != NULL )
			delete m_pRoot;

		m_pRoot = pRoot;
	}

	friend class GraphIterator<T>;
protected:
	GraphNode<T>* m_pRoot;	

private:
	// Reset visited flag
	void ResetVisitedFlag()
	{
		if( m_pRoot != NULL )
			m_pRoot->ResetVisitedFlag();
	}
};

#endif // __GRAPH_H__