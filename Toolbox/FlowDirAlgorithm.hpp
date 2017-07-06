#ifndef FLOWDIRALGORITHM_
#define FLOWDIRALGORITHM_

#include <iostream>

#include "GridCell.hpp"
#include "ArrayDEM.hpp"

using namespace std;

//do not need to fill depression
template<class elev_t>
void flow_dir_pf_d8(const string &filename, bool forceout) {
	ArrayDEM<elev_t> elevation(filename);
	ArrayDEM<uint8_t> flowdir;

	flowdir.resize(elevation, NO_FLOW);
	flowdir.setNoData(NO_FLOW);

	xy_t width = elevation.width();
	xy_t height = elevation.height();

	elev_t no_data = elevation.getNoData();

	GridCellZk_pq<elev_t> open;

	for (xy_t x = 0; x < width; x++) {
		for (xy_t y = 0; y < height; y++) {
			if (elevation(x, y) != no_data && elevation.isEdge(x, y)) {
				if (forceout) {
					//calculalte the edge cell flowdir
				}
				else {
					open.emplace(x, y, elevation(x, y));
				}
			}
		}
	}

	while (open.size() > 0) {
		auto c = open.top();
		open.pop();

		for (int n = 0; n < 8; n++) {
			xy_t nx = c.x + dx[n];
			xy_t ny = c.y + dy[n];

			if (elevation.inGrid(nx, ny) && elevation(nx, ny) != no_data && !elevation.isEdge(nx, ny) && flowdir(nx, ny) == NO_FLOW) {
				flowdir(nx, ny) = d8_arcgis_inverse[n];
				open.emplace(nx, ny, elevation(nx, ny));
			}
		}
	}

	flowdir.saveGDAL(elevation.dir + '\\' + elevation.filename + "-pf-d8.tif");
}

template<class elev_t>
static uint8_t d8_flow_dir_cell(ArrayDEM<elev_t> &elevations, xy_t x, xy_t y) {
	elev_t minimum_elevation = elevations(x, y);
	int flowdir = NO_FLOW;
	for (int n = 0; n < 8; n++)
		if (
			elevations(x + dx[n], y + dy[n])<minimum_elevation
			|| (elevations(x + dx[n], y + dy[n]) == minimum_elevation
				&& flowdir % 2 == 1 && n % 2 == 0) //TODO: What is this modulus stuff for?
			) {
			minimum_elevation = elevations(x + dx[n], y + dy[n]);
			flowdir = n;
		}

	return flowdir;
}

//need to fill depression (flat with priority-flood)
template<class elev_t>
void flow_dir_original_d8(const string &filename, bool forceout) {
	ArrayDEM<elev_t> elevation(filename);
	ArrayDEM<uint8_t> flowdir;

	flowdir.resize(elevation, NO_FLOW);
	flowdir.setNoData(NO_FLOW);

	GridCellZk_pq<elev_t> open;

	xy_t width = elevation.width(), height = elevation.height();
	elev_t no_data = elevation.getNoData();

	for (xy_t y = 0; y < height; y++) {
		for (xy_t x = 0; x < width; x++) {
			if (elevation(x, y) != no_data && elevation.isEdge(x, y)) {
				if (forceout) {
					//calculalte the edge cell flowdir
				}
				else {
					open.emplace(x, y, elevation(x, y));
				}
			}
		}
	}

	while (open.size() > 0) {
		auto c = open.top();
		open.pop();

		for (int n = 0; n < 8; n++) {
			xy_t nx = c.x + dx[n];
			xy_t ny = c.y + dy[n];

			if (elevation.inGrid(nx, ny) && elevation(nx, ny) != no_data && !elevation.isEdge(nx, ny) && flowdir(nx, ny) == NO_FLOW) {
				if (elevation(nx, ny) == c.z) {
					flowdir(nx, ny) = d8_arcgis_inverse[n];
					open.emplace(nx, ny, elevation(nx, ny));
				}
				else {
					flowdir(nx, ny) = d8_arcgis[d8_flow_dir_cell(elevation, nx, ny)];
					open.emplace(nx, ny, elevation(nx, ny));
				}
			}
		}
	}

	flowdir.saveGDAL(elevation.dir + '\\' + elevation.filename + "-original-d8.tif");
}

template<class elev_t>
void flow_dir_jrq_d8(const string &filename, bool forceout) {

}

#endif
