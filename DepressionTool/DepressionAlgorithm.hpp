#ifndef DEPRESSIONALGORITHM_
#define DEPRESSIONALGORITHM_

#include <iostream>

#include "GridCell.hpp"

using namespace std;

template<class elev_t>
void identify_depression(const string &filename)
{
	ArrayDEM<elev_t> dem(filename);
}

//fill depression(priority-flood)
template<class elev_t>
void fill_depression(const string &filename, bool isIdentify)
{
	ArrayDEM<elev_t> dem(filename);

	GridCellZ_pq<elev_t> open;
	queue<GridCellZ<elev_t>> pit;

	ArrayDEM<uint8_t> closed;
	closed.resize(dem, 0);
	closed.setNoData(0);

	elev_t no_data = dem.getNoData();

	//closed value 0, 1, 2, 3
	//0:no_data
	//1:not been processed
	//2:processed
	//3:pit
	//4:flat
	//put boundary cell into open and set closed to 2, set closed value to 1 that is not no_data
	for (int x = 0; x < dem.width(); x++)
	{
		for (int y = 0; y < dem.height(); y++)
		{
			if (dem(x, y) != no_data)
			{
				if (dem.isEdge(x, y))
				{
					open.emplace(x, y, dem(x, y));
					closed(x, y) = 2;
				}
				else
					closed(x, y) = 1;					
			}
		}
	}

	while (open.size() > 0 || pit.size() > 0)
	{
		GridCellZ<elev_t> c;
		if (pit.size() > 0)
		{
			c = pit.front();
			pit.pop();
		}
		else
		{
			c = open.top();
			open.pop();
		}
		for (int n = 1; n <= 8; n++)
		{
			int nx = c.x + dx[n];
			int ny = c.y + dy[n];

			if (dem.inGrid(nx, ny) && closed(nx, ny) == 1)
			{
				if (dem(nx, ny) <= c.z)
				{
					if (dem(nx, ny) < c.z)
					{
						dem(nx, ny) = c.z;
						closed(nx, ny) = 3;
					}
					else
						closed(nx, ny) = 4;
					pit.push(GridCellZ<elev_t>(nx, ny, c.z));
				}
				else
				{
					closed(nx, ny) = 2;
					open.emplace(nx, ny, dem(nx, ny));
				}
			}
		}
	}

	dem.saveGDAL(dem.dir + '\\' + dem.filename + "-fill.tif");

	if (isIdentify)
		closed.saveGDAL(dem.dir + '\\' + dem.filename + "-identify.tif");
}
#endif
