#ifndef DEPRESSIONALGORITHM_
#define DEPRESSIONALGORITHM_

#include <iostream>

using namespace std;

template<class elev_t>
void identify_depression(const string &filename)
{
	ArrayDEM<elev_t> dem(filename);
	dem.printStamp();
}
#endif
