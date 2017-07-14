#pragma once
#include <iostream>

template<class elev_t>
void flow_accu(const string &filename) {
	ArrayDEM<elev_t> dir(filename);

	ArrayDEM<uint32_t> accu;
	accu.resize(dir, 0);
	accu.setNoData(-1);

	ArrayDEM<uint8_t> input;
	input.resize(dir, 0);
	

	//初始化input数组
	


}