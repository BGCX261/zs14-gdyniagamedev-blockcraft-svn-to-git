#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include "NodeType.h"

class GraphNode
{
protected:
	int		mIndex;

public:
	GraphNode( int idx = invalid_node_index ):
	  mIndex(idx){}

	virtual ~GraphNode(){}

	int Index() const { return mIndex; }
	void SetIndex( const int& idx ) { mIndex = idx; }

};



#endif