#ifndef ASTAR_SEARCH_H
#define ASTAR_SEARCH_H

#include "SparseGraph.h"
#include <vector>
#include <list>
#include "GraphEdge.h"
#include "PriorityQueue.h"

class AStarSearch
{
private:
	SparseGraph&		mGraph;

	std::vector<const GraphEdge*>	mShortestPathTree;

	std::vector<float>				mCostToThisNode;

	std::vector<const GraphEdge*>	mSearchFrontier;

	int							mSource, mTarget;

	void Search()
	{
		//create an indexed priority queue that sorts smallest to largest
  //(front to back).Note that the maximum number of elements the iPQ
  //may contain is N. This is because no node can be represented on the 
  //queue more than once.
  IndexedPriorityQLow<float> pq(mCostToThisNode, mGraph.NumNodes());

  //put the source node on the queue
  pq.insert(mSource);

  //while the queue is not empty
  while(!pq.empty())
  {
    //get lowest cost node from the queue. Don't forget, the return value
    //is a *node index*, not the node itself. This node is the node not already
    //on the SPT that is the closest to the source node
    int NextClosestNode = pq.Pop();

    //move this edge from the frontier to the shortest path tree
    mShortestPathTree[NextClosestNode] = mSearchFrontier[NextClosestNode];

    //if the target has been found exit
    if (NextClosestNode == mTarget) return;

    //now to relax the edges.
	SparseGraph::EdgeIterator ConstEdgeItr(mGraph, NextClosestNode);

    //for each edge connected to the next closest node
    for (;!ConstEdgeItr.end();++ConstEdgeItr)
    {
		const GraphEdge* pE = ConstEdgeItr();
      //the total cost to the node this edge points to is the cost to the
      //current node plus the cost of the edge connecting them.
      float NewCost = mCostToThisNode[NextClosestNode] + pE->Cost();

      //if this edge has never been on the frontier make a note of the cost
      //to get to the node it points to, then add the edge to the frontier
      //and the destination node to the PQ.
      if (mSearchFrontier[pE->To()] == 0)
      {
        mCostToThisNode[pE->To()] = NewCost;

        pq.insert(pE->To());

        mSearchFrontier[pE->To()] = pE;
      }

      //else test to see if the cost to reach the destination node via the
      //current node is cheaper than the cheapest cost found so far. If
      //this path is cheaper, we assign the new cost to the destination
      //node, update its entry in the PQ to reflect the change and add the
      //edge to the frontier
      else if ( (NewCost < mCostToThisNode[pE->To()]) &&
                (mShortestPathTree[pE->To()] == 0) )
      {
        mCostToThisNode[pE->To()] = NewCost;

        //because the cost is less than it was previously, the PQ must be
        //re-sorted to account for this.
        pq.ChangePriority(pE->To());

        mSearchFrontier[pE->To()] = pE;
      }
    }
  }
	}

public:
	AStarSearch( SparseGraph& graph,
		int source,
		int target ):mGraph(graph),
					mShortestPathTree( graph.NumNodes() ),
					mCostToThisNode( graph.NumNodes() ),
					mSearchFrontier( graph.NumNodes() ),
					mSource( source ),
					mTarget( target )
	{
		Search();
	}

	std::vector<const GraphEdge*> SPT() const { return mShortestPathTree; }

	std::list<int> PathToTarget() const
	{
		std::list<int> path;

		//just return an empty path if no target or no path found
		if (mTarget < 0)  return path;

		int nd = mTarget;

		path.push_front(nd);

		while ((nd != mSource) && (mShortestPathTree[nd] != 0))
		{
			nd = mShortestPathTree[nd]->From();

			path.push_front(nd);
		}

		return path;
	}

	float CostToTarget() const { return mCostToThisNode[mTarget]; }

	float CostToNode(unsigned int node) const { return mCostToThisNode[node]; }

};



#endif