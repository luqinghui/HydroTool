#pragma once
#include <iostream>
#include <cmath>

template<class elev_t>
void flow_accu(const string &filename) {
	ArrayDEM<elev_t> dir(filename);

	ArrayDEM<uint32_t> accu;
	accu.resize(dir, 0);
	//accu.setNoData(-1);

	ArrayDEM<uint8_t> input;
	input.resize(dir, 0);
	

	//初始化input数组
	xy_t width = dir.width();
	xy_t height = dir.height();

	for (xy_t y = 0; y < height; y++)
		for (xy_t x = 0; x < width; x++)
			//neighbour
			for (int n = 0; n < 8; n++) {
				xy_t nx = x + dx[n];
				xy_t ny = y + dy[n];

				if (dir.inGrid(nx, ny) && !dir.isNoData(nx, ny) && dir(nx, ny) == d8_arcgis_inverse[n])
					++input(x, y);
			}
	
	//calc
	std::queue<GridCell> zero_inputs;
	for (xy_t y = 0; y < height; y++)
		for (xy_t x = 0; x < width; x++)
			if (!dir.isNoData(x, y) && input(x, y) == 0)
				zero_inputs.emplace(x, y);

	while (zero_inputs.size() > 0) {
		GridCell c = zero_inputs.front();
		zero_inputs.pop();

		int flow_dir = dir(c.x, c.y);
		if (flow_dir == NO_FLOW)
			continue;
		int n = int(log2(flow_dir) + 4) % 8;

		
		int nx = c.x + dx[n];
		int ny = c.y + dy[n];

		if (!dir.inGrid(nx, ny))
			continue;
		if (dir.isNoData(nx, ny))
			continue;

		accu(nx, ny) = accu(nx, ny) + accu(c.x, c.y);
		accu(nx, ny) = accu(nx, ny) + 1;
		--input(nx, ny);
		if (input(nx, ny) == 0)
			zero_inputs.emplace(nx, ny);
	}

	accu.saveGDAL(dir.dir + '\\' + dir.filename + "-accu.tif");
}