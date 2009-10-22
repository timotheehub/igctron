#ifndef __GRAPH_NODE_H__
#define __GRAPH_NODE_H__

#include <vector>

template< class T >
class GraphNode
{
public:
	GraphNode( GraphNode pRoot, const T* pData ) :
		m_pRoot( pRoot ), m_pData( pData )
	{}

	~GraphNode(void) {}

	void AddChild( GraphNode<T> node )
	{
		m_vChilds.add( node );
	}

	GraphNode<T>* GetRoot() const { return m_pRoot; }

	T* GetData() const { return m_pData; }

private:	
	GraphNode* m_pRoot;	
	std::vector< GraphNode<T> > m_vChilds;

	T* m_pData;	

};

#endif // __GRAPH_NODE_H__