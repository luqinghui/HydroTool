#ifndef GRIDCELL_
#define GRIDCELL_

#include <vector>
#include <queue>
#include <functional>

using namespace std;

class GridCell
{
public:
	int x;
	int y;
	GridCell() {}
	GridCell(int x, int y):x(x),y(y){}
};

template<class elev_t>
class GridCellZ: public GridCell
{
public:
	elev_t z;
	GridCellZ() {}
	GridCellZ(int x, int y, elev_t z):GridCell(x,y),z(z){}
	bool operator > (const GridCellZ<elev_t>& a) const { return z > a.z; }
};

template<class elev_t>
class GridCellZk : public GridCellZ<elev_t>
{
public:
	int k;
	GridCellZk(){}
	GridCellZk(int x, int y,elev_t z, int k):GridCellZ<elev_t>(x,y,z),k(k){}
	bool operator < (const GridCellZk<elev_t>& a) const { return GridCellZ<elev_t>::z < a.z; }
	bool operator > (const GridCellZk<elev_t>& a) const { return GridCellZ<elev_t>::z > a.z; }
};

template<typename elev_t>
using GridCellZ_pq = priority_queue<GridCellZ<elev_t>, vector<GridCellZ<elev_t>>, greater<GridCellZ<elev_t>>>;

template<typename elev_t>
class GridCellZk_pq: public priority_queue< GridCellZk<elev_t>, vector<GridCellZk<elev_t>>, greater<GridCellZk<elev_t>>>
{
private:
	uint64_t count = 0;
public:
	void push()
	{
		throw runtime_error("push() to GridCellZk_pq is not allowed!");
	}
	void emplace(int x, int y, elev_t z)
	{
		priority_queue<GridCellZk<elev_t>, vector<GridCellZk<elev_t>>, greater<GridCellZk<elev_t>>>::emplace(x, y, z, ++count);
	}
};


#endif
