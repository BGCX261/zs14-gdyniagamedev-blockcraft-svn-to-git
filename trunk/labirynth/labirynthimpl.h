#ifndef LABIRYNTH_IMPL_H
#define LABIRYNTH_IMPL_H

#include "grid.h"
#include "point.h"
#include "labirynthtile.h"
#include "pathfinding/SparseGraph.h"

using namespace cimg_library;
using namespace std;

class LabirynthImpl{
public:
	LabirynthImpl();
	~LabirynthImpl();
	void processLMB();
	void processRMB();
	bool buttonPressed();
	void draw();
	Point getKeyPointCoords(LabirynthTile*);
	void removeKeyPoint(LabirynthTile*);
	void buildGraph();
	vector<Point> findPath(const Point&,const Point&, int* outCost = NULL);

private:
	Grid<LabirynthTile> grid_;
	LabirynthTile *btnFrame_, *btnWall_, *btnStart_, *btnFinish_, *btnCurrent_;
	Sprite* btnSearch_;
	LabirynthTile *start_, *finish_;
	SparseGraph		pathfindingGraph_;
	bool	plotPath_;
	vector<Point> path_;
};

#endif

