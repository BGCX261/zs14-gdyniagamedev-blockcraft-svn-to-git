#ifndef SPARSE_GRAPH_H
#define SPARSE_GRAPH_H


#include <list>
#include <vector>
#include "GraphNode.h"
#include "GraphEdge.h"
#include <cassert>


class SparseGraph
{

public:
	typedef std::vector<GraphNode>	NodeVector;
	typedef std::list<GraphEdge>		EdgeList;
	typedef std::vector<EdgeList>	EdgeListVector;

	SparseGraph(): mNextNodeIndex(0){}

	int NumNodes() const { return (int)mNodes.size(); }

	int AddNode(const GraphNode& node)
	{ 
		if (node.Index() < (int)mNodes.size())
		{
			//make sure the client is not trying to add a node with the same ID as
			//a currently active node
			assert (mNodes[node.Index()].Index() == invalid_node_index &&
				"Attempting to add a node with a duplicate ID");

			mNodes[node.Index()] = node;

			return mNextNodeIndex;
		}

		else
		{
			//make sure the new node has been indexed correctly
			assert (node.Index() == mNextNodeIndex && "<SparseGraph::AddNode>:invalid index");

			mNodes.push_back(node);
			mEdges.push_back(EdgeList());//necessary?

			return mNextNodeIndex++;
		}
	}

	void AddEdge( int node, const GraphEdge& edge )
	{
		//first make sure the from and to nodes exist within the graph 
		assert( (edge.From() < mNextNodeIndex) && (edge.To() < mNextNodeIndex) &&
			"<SparseGraph::AddEdge>: invalid node index");

		//make sure both nodes are active before adding the edge
		if ( (mNodes[edge.To()].Index() != invalid_node_index) && 
			(mNodes[edge.From()].Index() != invalid_node_index))
		{
			//add the edge, first making sure it is unique
			if (UniqueEdge(edge.From(), edge.To()))
			{
				mEdges[edge.From()].push_back(edge);
			}

			//check to make sure the edge is unique before adding
			/*if (UniqueEdge(edge.To(), edge.From()))
			{
				GraphEdge NewEdge = edge;

				NewEdge.SetTo(edge.From());
				NewEdge.SetFrom(edge.To());

				mEdges[edge.To()].push_back(NewEdge);
			}*/

		}	
	}

	bool UniqueEdge(int from, int to) const
	{
		for (EdgeList::const_iterator curEdge = mEdges[from].begin();
			curEdge != mEdges[from].end();
			++curEdge)
		{
			if (curEdge->To() == to)
			{
				return false;
			}
		}

		return true;
	}

	//clears the graph ready for new node insertions
  void Clear(){mNextNodeIndex = 0; mNodes.clear(); mEdges.clear();}

private:
	NodeVector		mNodes;
	EdgeListVector	mEdges;
	int				mNextNodeIndex;

	friend class EdgeIterator;

public:

	class EdgeIterator
      {
      private:                                                                

        EdgeList::iterator	curEdge;
        SparseGraph&		G;
        const int           NodeIndex;

      public:

        EdgeIterator(SparseGraph&	graph,
                     int	        node): G(graph),
                                           NodeIndex(node)
        {
          /* we don't need to check for an invalid node index since if the node is
             invalid there will be no associated edges
         */

          curEdge = G.mEdges[NodeIndex].begin();
        }

        EdgeList::iterator  begin()
        {        
          curEdge = G.mEdges[NodeIndex].begin();
		  return curEdge;
        }

		GraphEdge* operator()()
		{
			if ( !end() )
			{
				return &(*curEdge);
			}
			return NULL;
		}

        EdgeList::iterator operator ++()
        {
			return ++curEdge;
        }

		EdgeList::iterator operator ++(int i)
        {
			return ++curEdge;
        }

        //return true if we are at the end of the edge list
        bool end()
        {
          return (curEdge == G.mEdges[NodeIndex].end());
        }
      };



};



#endif