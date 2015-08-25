#ifndef GRAPH_EDGE_TYPES_H
#define GRAPH_EDGE_TYPES_H

#include "NodeType.h"


class GraphEdge
{
protected:
	int		mFrom, mTo;
	float	mCost;

public:
	GraphEdge( int from, int to, float cost = 1.0f ):
	  mFrom( from ), mTo( to ), mCost( cost ) {}

	GraphEdge():mFrom( invalid_node_index ), mTo( invalid_node_index ), mCost( 1.0f ) {}

	virtual ~GraphEdge() {}

	int From() const { return mFrom; }
	void SetFrom( const int& from ) { mFrom = from; }

	int To() const { return mTo; }
	void SetTo( const int& to ) { mTo = to; }

	float Cost() const { return mCost; }
	void SetCost( const float& cost ) { mCost = cost; }

	bool operator == ( const GraphEdge& rhs )
	{
		return !( mFrom != rhs.mFrom ||
			mTo != rhs.mTo ||
			mCost != rhs.mCost );
	}

	bool operator != ( const GraphEdge& rhs )
	{
		return ! ( (*this) == rhs );
	}

	friend class EdgeCostComparator;
};


class EdgeCostComparator
{
public:
	bool operator()(const GraphEdge& lhs, const GraphEdge& rhs)
	{
		return lhs.mCost < rhs.mCost;
	}
};


#endif