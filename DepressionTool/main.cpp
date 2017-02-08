#include <gdal_priv.h>
#include <iostream>

#include "ToolMethod.hpp"
#include "ArrayDEM.hpp"
#include "DepressionAlgorithm.hpp"

using namespace std;

int main(void)
{
	string filename = "d:\\Pictures\\changwu.tif";
	GDALDataType dataType = getGDALType(filename);
	bool isIdentify = true;
	
	switch (dataType) 
	{
		case GDT_Unknown:
			cerr << "Unrecognised data type: " << dataType << endl;
			return -1;
		case GDT_Byte:
			fill_depression<uint8_t >(filename, isIdentify);
			break;
		case GDT_UInt16:
			fill_depression<uint16_t >(filename, isIdentify);
			break;
		case GDT_Int16:
			fill_depression<int16_t >(filename, isIdentify);
			break;
		case GDT_UInt32:
			fill_depression<uint32_t >(filename, isIdentify);
			break;
		case GDT_Int32:
			fill_depression<int32_t >(filename, isIdentify);
			break;
		case GDT_Float32:
			fill_depression<float >(filename, isIdentify);
			break;
		case GDT_Float64:
			fill_depression<double >(filename, isIdentify);
			break;
		case GDT_CInt16:
		case GDT_CInt32:
		case GDT_CFloat32:
		case GDT_CFloat64:
			cerr << "Complex types are unsupported. Sorry!" << endl;
			return -1;
		default:
			cerr << "Unrecognised data type: " << dataType << endl;
			return -1;
	}
	return 0;
}