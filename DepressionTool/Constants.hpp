/*

234
105
876

32 64 128
16  0   1
8  4   2

*/
#ifndef CONSTANTS_
#define CONSTANTS_

#include <iostream>

//D8 Neighbour Directions

//                  0   1   2   3   4  5  6  7   8
const int dx[9] = { 0, -1, -1,  0,  1, 1, 1, 0, -1 };
const int dy[9] = { 0,  0, -1, -1, -1, 0, 1, 1,  1 };

const int d8_inverse[9] = { 0,5,6,7,8,1,2,3,4 };

//Arrows indicating flow directions
const wchar_t fdarrows[9] = { L'¡¤',L'¡û',L'¨I',L'¡ü',L'¨J',L'¡ú',L'¨K',L'¡ý',L'¨L' };

//sqrt(2), used to generate distances from a central cell to its neighbours
const double SQRT2 = 1.414213562373095048801688724209698078569671875376948;

//Distances from a central cell to each of its 8 neighbours
const double dr[9] = { 0,1,SQRT2,1,SQRT2,1,SQRT2,1,SQRT2 };

const uint8_t d8_arcgis[9] = { 0,16,32,64,128,1,2,4,8 };
const uint8_t d8_arcgis_inverse[9] = { 0,1,2,4,8,16,32,64,128 };

//Used to indicate that a flowdir cell is NoData
const uint8_t FLOWDIR_NO_DATA = 255;

//Value used to indicate that a cell does not have a defined flow direction
//(i.e. that it has no local gradient)
const uint8_t NO_FLOW = 0;

//Value used to indicate that a flow accumulation cell is NoData
const int32_t ACCUM_NO_DATA = -1;

#endif