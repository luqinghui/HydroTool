#pragma once

#include <iostream>
#include <list>

#include "GridCell.hpp"

using namespace std;

//fill depression(priority-flood)
template<class elev_t>
void fill_depressions(const string &filename) {
	ArrayDEM<elev_t> elevation(filename);

	GridCellZ_pq<elev_t> slopes;
	queue<GridCellZ<elev_t>> pits;
	queue<GridCellZ<elev_t>> flats;


	ArrayDEM<uint8_t> closed;
	closed.resize(elevation, 0);
	closed.setNoData(0);

	xy_t width = elevation.width();
	xy_t height = elevation.height();

	for (xy_t x = 0; x < width; x++) {
		for (xy_t y = 0; y < height; y++) {
			if (!elevation.isNoData(x, y)) {
				if (elevation.isEdge(x, y)) {
					slopes.emplace(x, y, elevation(x, y));
					closed(x, y) = 2;
				}
				else
					closed(x, y) = 1;
			}
		}
	}

	while (slopes.size() > 0 || pits.size() > 0 || flats.size() > 0) {
		GridCellZ<elev_t> c;
		if (pits.size() > 0) {
			c = pits.front();
			pits.pop();
		}
		else if (flats.size() > 0) {
			c = flats.front();
			flats.pop();
		}
		else {
			c = slopes.top();
			slopes.pop();
		}
		for (int n = 0; n < 8; n++) {
			int nx = c.x + dx[n];
			int ny = c.y + dy[n];

			if (elevation.inGrid(nx, ny) && closed(nx, ny) == 1) {
				if (elevation(nx, ny) < c.z) {
					elevation(nx, ny) = c.z;
					pits.push(GridCellZ<elev_t>(nx, ny, c.z));
				}
				else if (elevation(nx, ny) == c.z)
					flats.push(GridCellZ<elev_t>(nx, ny, c.z));
				else
					slopes.emplace(nx, ny, elevation(nx, ny));
				closed(nx, ny) = 2;
			}
		}
	}

	elevation.saveGDAL(elevation.dir + '\\' + elevation.filename + "-fill.tif");
}

struct InfoStruct {
	int32_t x;
	int32_t y;
	uint32_t count;
};

//get the depressions information
template<class elev_t>
void identify_depressions(const string &filename) {
	std::list<InfoStruct> infos;

	ArrayDEM<elev_t> elevation(filename);
	ArrayDEM<uint8_t> depression;

	depression.resize(elevation, 0);
	depression.setNoData(0);

	GridCellZ_pq<elev_t> open;
	queue<GridCellZ<elev_t>> pit;
	queue<GridCellZ<elev_t>> flat;

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
					depression(x, y) = 1;
			}
		}
	}

	//1: cell had value but have not been proceed
	//0:  slope
	bool is_pour = false;
	int32_t id = -1;
	while (open.size() > 0 || pit.size() > 0 || flat.size() > 0) {
		GridCellZ<elev_t> c;
		if (pit.size() > 0) {
			c = pit.front();
			pit.pop();
		}
		else {
			if (is_pour == false)
				is_pour = true;
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

			if (elevation.inGrid(nx, ny) && depression(nx, ny) == 1) {
				if (elevation(nx, ny) < c.z) {
					//if (is_pour) {
					//	is_pour = false;
					//	infos.push_back(InfoStruct());
					//	infos.back().x = c.x;
					//	infos.back().y = c.y;
					//	infos.back().count = 1;
					//	depression(c.x, c.y) = 2;
					//}
					if (is_pour) {
						is_pour = false;
						infos.push_back(InfoStruct());
						infos.back().x =nx;
						infos.back().y = ny;
						infos.back().count = 1;
						depression(nx, ny) = 2;
					}
					infos.back().count += 1;
					pit.push(GridCellZ<elev_t>(nx, ny, c.z));
					depression(nx, ny) += 2;	//标识洼地
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

	//输出洼地信息文件
	SaveInfoToCSV(infos, elevation.dir + '\\' + elevation.filename + "-pits.csv");
	//保存洼地
	depression.saveGDAL(elevation.dir + '\\' + elevation.filename + "-pits.tif", GDT_Byte);
}

//get the flats information
template<class elev_t>
void identify_flats(const string &filename) {

}

template<class elev_t>
void identify_nested_depressions(const string &filename) {
	ArrayDEM<elev_t> elevation(filename);

	ArrayDEM<uint8_t> pits;	//result
	pits.resize(elevation, 0);
	pits.setNoData(0);

	xy_t width = elevation.width();
	xy_t height = elevation.height();

	

	pits.saveGDAL(elevation.dir + '\\' + elevation.filename + "-nested-pits.tif");
}

void SaveInfoToCSV(std::list<InfoStruct> infos, string &filename) {
	FILE *f;
	f = fopen(filename.c_str(), "w");
	for each (InfoStruct info in infos) {
		fprintf(f, "%d,%d,%d\n", info.x, info.y, info.count);
	}
	fclose(f);
}