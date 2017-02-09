#ifndef DEPRESSIONALGORITHM_
#define DEPRESSIONALGORITHM_

#include <iostream>

#include "GridCell.hpp"

using namespace std;

//fill depression(priority-flood)
template<class elev_t>
void fill_depression(const string &filename, bool isIdentify) {
	ArrayDEM<elev_t> elevation(filename);

	GridCellZ_pq<elev_t> open;
	queue<GridCellZ<elev_t>> pit;

	ArrayDEM<uint8_t> closed;
	closed.resize(elevation, 0);
	closed.setNoData(0);

	elev_t no_data = elevation.getNoData();

	xy_t width = elevation.width();
	xy_t height = elevation.height();

	//closed value 0, 1, 2, 3
	//0:no_data
	//1:not been processed
	//2:processed
	//3:pit
	//4:flat
	//put boundary cell into open and set closed to 2, set closed value to 1 that is not no_data
	for (xy_t x = 0; x < width; x++) {
		for (xy_t y = 0; y < height; y++) {
			if (elevation(x, y) != no_data) {
				if (elevation.isEdge(x, y)) {
					open.emplace(x, y, elevation(x, y));
					closed(x, y) = 2;
				}
				else
					closed(x, y) = 1;
			}
		}
	}

	while (open.size() > 0 || pit.size() > 0) {
		GridCellZ<elev_t> c;
		if (pit.size() > 0) {
			c = pit.front();
			pit.pop();
		}
		else {
			c = open.top();
			open.pop();
		}
		for (int n = 0; n < 8; n++) {
			int nx = c.x + dx[n];
			int ny = c.y + dy[n];

			if (elevation.inGrid(nx, ny) && closed(nx, ny) == 1) {
				if (elevation(nx, ny) <= c.z) {
					if (elevation(nx, ny) < c.z) {
						elevation(nx, ny) = c.z;
						closed(nx, ny) = 3;
					}
					else
						closed(nx, ny) = 4;
					pit.push(GridCellZ<elev_t>(nx, ny, c.z));
				}
				else {
					closed(nx, ny) = 2;
					open.emplace(nx, ny, elevation(nx, ny));
				}
			}
		}
	}

	elevation.saveGDAL(elevation.dir + '\\' + elevation.filename + "-fill.tif");

	if (isIdentify)
		closed.saveGDAL(elevation.dir + '\\' + elevation.filename + "-identify.tif");
}

//get the depressions information
template<class elev_t>
void identify_depression(const string &filename) {
	ArrayDEM<elev_t> elevation(filename);
	ArrayDEM<uint32_t> depression;

	depression.resize(elevation, -2);
	depression.setNoData(-2);

	GridCellZ_pq<elev_t> open;
	queue<GridCellZ<elev_t>> pit;
	queue<GridCellZ<elev_t>> flat;

	queue<GridCell> pour;

	elev_t no_data = elevation.getNoData();

	xy_t width = elevation.width();
	xy_t height = elevation.height();

	for (xy_t x = 0; x < width; x++) {
		for (xy_t y = 0; y < height; y++) {
			if (elevation(x, y) != no_data) {
				if (elevation.isEdge(x, y)) {
					open.emplace(x, y, elevation(x, y));
					depression(x, y) = 0;
				}
				else
					depression(x, y) = -1;
			}
		}
	}

	//-2: nodata
	//-1: cell had value
	//0:  processed
	//
	bool first = false;
	uint32_t count = 0;
	while (open.size() > 0 || pit.size() > 0 || flat.size() > 0) {
		GridCellZ<elev_t> c;
		if (pit.size() > 0) {
			c = pit.front();
			pit.pop();
		}
		else {
			if (first == false) {
				first = true;
				++count;
			}
			if (flat.size() > 0) {
				c = flat.front();
				flat.pop();
			}
			else {
				c = open.top();
				open.pop();
			}
		}
		for (int n = 0; n < 8; n++) {
			xy_t nx = c.x + dx[n];
			xy_t ny = c.y + dy[n];

			if (elevation.inGrid(nx, ny) && depression(nx, ny) == -1) {
				if (elevation(nx, ny) < c.z) {
					if (first) {
						first = false;
						pour.push(GridCell(nx, ny));
					}
					pit.push(GridCellZ<elev_t>(nx, ny, c.z));
					depression(nx, ny) = count;
				}
				else if (elevation(nx, ny) == c.z) {
					flat.push(GridCellZ<elev_t>(nx, ny, c.z));
					depression(nx, ny) = 0;
				}
				else {
					open.emplace(nx, ny, elevation(nx, ny));
					depression(nx, ny) = 0;
				}
			}
		}
	}

	depression.saveGDAL(elevation.dir + '\\' + elevation.filename + "-pits-info.tif");
}


template<class elev_t>
void NestedDepression(const string &filename) {
	ArrayDEM<elev_t> elevation(filename);

}

#endif
