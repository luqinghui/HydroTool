#include <gdal_priv.h>
#include <iostream>

#include "ToolMethod.hpp"
#include "ArrayDEM.hpp"
#include "DepressionAlgorithm.hpp"

using namespace std;

int main(void)
{
	string filename = "d:\\Pictures\\sample.jpg";
	GDALDataType dataType = getGDALType(filename);
	
	switch (dataType) 
	{
		case GDT_Unknown:
			cerr << "Unrecognised data type: " << dataType << endl;
			return -1;
		case GDT_Byte:
			identify_depression<uint8_t >(filename);
			break;
		case GDT_UInt16:
			identify_depression<uint16_t >(filename);
			break;
		case GDT_Int16:
			identify_depression<int16_t >(filename);
			break;
		case GDT_UInt32:
			identify_depression<uint32_t >(filename);
			break;
		case GDT_Int32:
			identify_depression<int32_t >(filename);
			break;
		case GDT_Float32:
			identify_depression<float >(filename);
			break;
		case GDT_Float64:
			identify_depression<double >(filename);
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