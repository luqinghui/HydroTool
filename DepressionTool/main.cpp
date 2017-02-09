#include <gdal_priv.h>
#include <iostream>

#include "ToolMethod.hpp"
#include "ArrayDEM.hpp"
#include "DepressionAlgorithm.hpp"
#include "FlowDirAlgorithm.hpp"

using namespace std;

int flow_dir_pf_d8_alg(const string &filename, bool forceout);
int flow_dir_original_d8_alg(const string &filename, bool forceout);
int fill_depression_alg(const string &filename, bool isIdentify);
int identify_depression_alg(const string &filename);

int main(void) {
	string filename = "d:\\Pictures\\changwu-fill.tif";

	flow_dir_original_d8_alg(filename, false);

	//fill_depression_alg(filename, false);

	//identify_depression_alg(filename);

	return 0;
}

int flow_dir_original_d8_alg(const string &filename, bool forceout) {
	GDALDataType dataType = getGDALType(filename);

	switch (dataType) {
	case GDT_Unknown:
		cerr << "Unrecognised data type: " << dataType << endl;
		return -1;
	case GDT_Byte:
		flow_dir_original_d8<uint8_t >(filename, forceout);
		break;
	case GDT_UInt16:
		flow_dir_original_d8<uint16_t >(filename, forceout);
		break;
	case GDT_Int16:
		flow_dir_original_d8<int16_t >(filename, forceout);
		break;
	case GDT_UInt32:
		flow_dir_original_d8<uint32_t >(filename, forceout);
		break;
	case GDT_Int32:
		flow_dir_original_d8<int32_t >(filename, forceout);
		break;
	case GDT_Float32:
		flow_dir_original_d8<float >(filename, forceout);
		break;
	case GDT_Float64:
		flow_dir_original_d8<double >(filename, forceout);
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

int flow_dir_pf_d8_alg(const string &filename, bool forceout) {
	GDALDataType dataType = getGDALType(filename);

	switch (dataType) {
	case GDT_Unknown:
		cerr << "Unrecognised data type: " << dataType << endl;
		return -1;
	case GDT_Byte:
		flow_dir_pf_d8<uint8_t >(filename, forceout);
		break;
	case GDT_UInt16:
		flow_dir_pf_d8<uint16_t >(filename, forceout);
		break;
	case GDT_Int16:
		flow_dir_pf_d8<int16_t >(filename, forceout);
		break;
	case GDT_UInt32:
		flow_dir_pf_d8<uint32_t >(filename, forceout);
		break;
	case GDT_Int32:
		flow_dir_pf_d8<int32_t >(filename, forceout);
		break;
	case GDT_Float32:
		flow_dir_pf_d8<float >(filename, forceout);
		break;
	case GDT_Float64:
		flow_dir_pf_d8<double >(filename, forceout);
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

int identify_depression_alg(const string &filename) {
	GDALDataType dataType = getGDALType(filename);

	switch (dataType) {
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

int fill_depression_alg(const string &filename, bool isIdentify) {
	GDALDataType dataType = getGDALType(filename);

	switch (dataType) {
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