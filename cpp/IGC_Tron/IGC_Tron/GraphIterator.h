#ifndef __GRAPHITERATOR_H__
#define __GRAPHITERATOR_H__

#include <stack>
#include "GraphNode.h"

template < class T >
class GraphIterator
{
public:
	// Constructor
	GraphIterator( GraphNode<T>* pBegin = NULL, GraphNode<T>* pEnd = NULL ) :
	  m_pBegin( pBegin ), m_pCurrent( m_pBegin ), m_pEnd( pEnd )
	 {
		 if( m_pBegin != NULL )
			 m_pBegin->ResetVisitedFlag();
	 }

    // Destructor
	~GraphIterator(void)
	{
	}
	
	// Determines if there is an other node to visit using DFS algorithm
	bool HasNext()
	{
		if( m_pCurrent != m_pEnd )
		{
			GraphNode<T>* rightState = NULL;
			while( rightState == NULL )
			{
				std::list< GraphNode<T>* > childList;
				childList = m_pCurrent->GetChildList();

				std::list< GraphNode<T>* >::iterator i;
				i = childList.begin();

				// Walk through the graph and try to get a non-visited state
				while( i != childList.end() && rightState == NULL )
				{
					if( (*i)->IsVisited() == false )
					{
						m_Stack.push( m_pCurrent );
						rightState = (*i);
					}

					i++;
				}

				// if they are all visited
				if( rightState == NULL )
				{
					// No predecessor
					if( m_Stack.size() == 0 )
					{
						m_pCurrent = rightState = NULL;
						return false;
					}
					else
					{
						// Get predecessor
						m_pCurrent = m_pCurrent->GetParentNode();
						m_Stack.pop();
					}
				}
			}
			
			m_pCurrent = rightState;
			if( m_pCurrent != NULL )			
				m_pCurrent->SetVisited();
		}

		return (m_pCurrent != NULL) || (m_pCurrent == m_pEnd);
	}

	GraphNode< T >* CurrentNode()
	{
		return m_pCurrent;
	}

protected:
	GraphNode<T>* m_pBegin;	
	GraphNode<T>* m_pEnd;

	GraphNode<T>* m_pCurrent;

	std::stack< GraphNode<T>* > m_Stack;
};

#endif // __GRAPHITERATOR_H__