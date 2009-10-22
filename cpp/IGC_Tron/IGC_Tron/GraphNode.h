/****************************************************
* Class : GraphNode									*
* Author : Sébastien M.                             *
* Represents a node of a graph which can also have	*
* children.										    *
****************************************************/

#ifndef __GRAPH_NODE_H__
#define __GRAPH_NODE_H__

#include <list>
#include <iostream>

template< class T >
class GraphNode
{
public:
	// Constructor
	GraphNode( GraphNode<T>* pParent, T* pData = NULL ) :
		m_pParent( pParent ), m_pData( pData ), visited( false )
	{
		if( m_pParent != NULL )
			m_pParent->AddChild( this );
	}

	// Destructor
	~GraphNode(void)
	{
#ifdef _DEBUG
		std::cout << "Destroyed." << endl;
#endif


		std::list< GraphNode<T>* >::iterator i;
		for( i = m_ChildsList.begin(); i != m_ChildsList.end(); i++ )		
		{
			if( (*i) != NULL )
			{
				delete (*i);		
				(*i) = NULL;
			}
		}

		delete m_pData;
	}

	// Add a child to this node if it never had been added before
	void AddChild( GraphNode<T>* node )
	{
		if( IsChild( node ) == false )
			m_ChildsList.push_back( node );			
	}

	// Removes a child
	void RemoveChild( GraphNode<T>* node )
	{				
		m_ChildsList.remove( node );	
	}

	// Removes itself from the graph
	void Remove()
	{
		if( m_pParent != NULL )
		{
			m_pParent->RemoveChild( this );
		}		
	}

	// Check if a node is a child or not
	bool IsChild( GraphNode<T>* node )
	{				
		std::list< GraphNode<T>* >::iterator i;
		i = m_ChildsList.begin();

		bool boFound = false;
		while( !boFound && i!= m_ChildsList.end() )		
		{
			if( (*i) == node )
				boFound = true;
			else
				i++;
		}		

		return boFound;
	}

	// Get child list
	std::list< GraphNode<T>* >& GetChildList()
	{
		return m_ChildsList;
	}

	// Returns node parent pointer
	GraphNode<T>* GetParentNode() const
	{ 
		return m_pParent;
	}

	// Returns a pointer to the T object
	T* GetData()
	{ 
		return m_pData;
	}

	// Has this node been visited while browsing ?
	bool IsVisited()
	{
		return visited;
	}

	// This node has been visited while browsing the graph
	void SetVisited()
	{
		visited = true;
	}

	// Reset visited flag to false
	void ResetVisitedFlag()
	{
		std::list< GraphNode<T>* >::iterator i;

		for( i = m_ChildsList.begin(); i != m_ChildsList.end(); i++ )
			(*i)->ResetVisitedFlag();

		visited = false;
	}
protected:	
	// Parent node
	GraphNode* m_pParent;	

	// Node children
	std::list< GraphNode<T>* > m_ChildsList;	

	// Associated data
	T* m_pData;	

	// To browse the graph
	bool visited;
};

#endif // __GRAPH_NODE_H__