#pragma once

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

	GridCellZk_pq<elev_t> open;

	for (xy_t x = 0; x < width; x++) {
		for (xy_t y = 0; y < height; y++) {
			if ((!elevation.isNoData(x, y)) && elevation.isEdge(x, y)) {
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

		for (int n = 1; n <= 8; n++) {
			xy_t nx = c.x + dx[n];
			xy_t ny = c.y + dy[n];

			if (elevation.inGrid(nx, ny) && (!elevation.isNoData(nx, ny)) && !elevation.isEdge(nx, ny) && flowdir(nx, ny) == NO_FLOW) {
				flowdir(nx, ny) = d8_arcgis_inverse[n];
				open.emplace(nx, ny, elevation(nx, ny));
			}
		}
	}

	flowdir.saveGDAL(elevation.dir + '\\' + elevation.filename + "-pf-d8.tif");
}

template<class elev_t>
uint8_t d8_flow_dir_cell(ArrayDEM<elev_t> &elevations, xy_t x, xy_t y) {
	int flowdir = NO_FLOW;
	double max = DBL_MIN;

	if (elevations.isEdge(x, y))
		return flowdir;

	double diffs[8];
	for (int n = 1; n <= 8; n++)
		if (!elevations.isNoData(x + dx[n], y + dy[n]))
			diffs[n] = (elevations(x, y) - elevations(x + dx[n], y + dy[n]))/dr[n];
	
	//condition1：
	//最大坡降为负，洼地
	//赋值NO_FLOW，在填洼过的DEM中不可能出现

	//condition2：
	//最大坡降为正，且只有一个方向，正常情况

	//condition3：
	//最大坡降为正，多于一个，
	//method1：参考J&D, table look-up
	//method2：扩大窗口范围（ArcGIS）
	//method3：随机选择
	//method4：顺序选择

	//condition4：
	//最大坡降为0，平地
	//如果只有一个，赋值该方向
	//若大于一个，暂不作处理，赋值NO_FLOW	

	return flowdir;
}

template<class elev_t>
uint8_t d8_flow_dir_cell_forceout(ArrayDEM<elev_t> &elevations, xy_t x, xy_t y) {
	int flowdir = NO_FLOW;

	if (elevations.isEdge(x, y)) {
		//修改,未考虑不规则形状
		if (elevations.isTopLeft(x, y))
			return 2;
		else if (elevations.isBottomLeft(x, y))
			return 8;
		else if (elevations.isTopRight(x, y))
			return 4;
		else if (elevations.isBottomRight(x, y))
			return 6;
		else if (elevations.isLeftCol(x, y))
			return 1;
		else if (elevations.isRightCol(x, y))
			return 5;
		else if (elevations.isTopRow(x, y))
			return 3;
		else if (elevations.isBottomRow(x, y))
			return 7;	
	}

	elev_t min = elevations(x, y) - elevations(x - 1, y);
	for (int n = 0; n < 8; n++)
		if (!elevations.isNoData(x+dx[n],y+dy[n])) {
			if (elevations(x + dx[n], y + dy[n]) < elevations(x, y)) {
				elev_t diff = elevations(x, y) - elevations(x + dx[n], y + dy[n]);
				if (n % 2 == 0)
					diff /= 1.414;
				if (diff < min) {
					min = diff;
					flowdir = n;
				}
			}
			
		}
	return flowdir;
}

//need to fill depression (flat have no flow dir)
template<class elev_t>
void flow_dir_original_d8_flats_no_flow(const string &filename, bool forceout) {
	ArrayDEM<elev_t> elevation(filename);
	ArrayDEM<uint8_t> flowdir;

	flowdir.resize(elevation, NO_FLOW);
	flowdir.setNoData(NO_FLOW);

	xy_t width = elevation.width();
	xy_t height = elevation.height();
	
	uint8_t(*flow_dir_cell)(ArrayDEM<elev_t>&, xy_t, xy_t) = nullptr;
	if (forceout)
		flow_dir_cell = &d8_flow_dir_cell_forceout;
	else
		flow_dir_cell = &d8_flow_dir_cell;

	//non-flats flow direction
	for (int y = 0; y<height; y++) {
		for (int x = 0; x<width; x++)
			if (elevation.isNoData(x, y))
				flowdir(x, y) = NO_FLOW;
			else {
				uint8_t n = flow_dir_cell(elevation, x, y);
				flowdir(x, y) = d8_arcgis[n];
			}
				
	}

	//flats flow direction




	flowdir.saveGDAL(elevation.dir + '\\' + elevation.filename + "-orignal-d8.tif");
}

template<class elev_t>
void flow_dir_jrq_d8(const string &filename, bool forceout) {

}
