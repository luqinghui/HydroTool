#include "HydroFunction.hpp"

using namespace std;

//原始D8
int __stdcall flow_dir_original_d8_alg(char *filename_char, bool forceout) {
	const string filename(filename_char);
	GDALDataType dataType = getGDALType(filename);

	switch (dataType) {
	case GDT_Unknown:
		cerr << "Unrecognised data type: " << dataType << endl;
		return -1;
	case GDT_Byte:
		flow_dir_original_d8_flats_no_flow<uint8_t >(filename, forceout);
		break;
	case GDT_UInt16:
		flow_dir_original_d8_flats_no_flow<uint16_t >(filename, forceout);
		break;
	case GDT_Int16:
		flow_dir_original_d8_flats_no_flow<int16_t >(filename, forceout);
		break;
	case GDT_UInt32:
		flow_dir_original_d8_flats_no_flow<uint32_t >(filename, forceout);
		break;
	case GDT_Int32:
		flow_dir_original_d8_flats_no_flow<int32_t >(filename, forceout);
		break;
	case GDT_Float32:
		flow_dir_original_d8_flats_no_flow<float >(filename, forceout);
		break;
	case GDT_Float64:
		flow_dir_original_d8_flats_no_flow<double >(filename, forceout);
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

//Priority-Flood D8
int __stdcall flow_dir_pf_d8_alg(char *filename_char, bool forceout) {
	const string filename(filename_char);
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

//识别洼地
int __stdcall identify_depression_alg(char *filename_char) {
	const string filename(filename_char);
	GDALDataType dataType = getGDALType(filename);

	switch (dataType) {
	case GDT_Unknown:
		cerr << "Unrecognised data type: " << dataType << endl;
		return -1;
	case GDT_Byte:
		identify_depressions<uint8_t >(filename);
		break;
	case GDT_UInt16:
		identify_depressions<uint16_t >(filename);
		break;
	case GDT_Int16:
		identify_depressions<int16_t >(filename);
		break;
	case GDT_UInt32:
		identify_depressions<uint32_t >(filename);
		break;
	case GDT_Int32:
		identify_depressions<int32_t >(filename);
		break;
	case GDT_Float32:
		identify_depressions<float >(filename);
		break;
	case GDT_Float64:
		identify_depressions<double >(filename);
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

//填充洼地
int __stdcall fill_depression_alg(char *filename_char) {
	const string filename(filename_char);
	GDALDataType dataType = getGDALType(filename);

	switch (dataType) {
	case GDT_Unknown:
		cerr << "Unrecognised data type: " << dataType << endl;
		return -1;
	case GDT_Byte:
		fill_depressions<uint8_t >(filename);
		break;
	case GDT_UInt16:
		fill_depressions<uint16_t >(filename);
		break;
	case GDT_Int16:
		fill_depressions<int16_t >(filename);
		break;
	case GDT_UInt32:
		fill_depressions<uint32_t >(filename);
		break;
	case GDT_Int32:
		fill_depressions<int32_t >(filename);
		break;
	case GDT_Float32:
		fill_depressions<float >(filename);
		break;
	case GDT_Float64:
		fill_depressions<double >(filename);
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

//汇流累积量
int __stdcall flow_accu_alg(char *filename_char) {
	const string filename(filename_char);
	GDALDataType dataType = getGDALType(filename);

	switch (dataType) {
	case GDT_Unknown:
		cerr << "Unrecognised data type: " << dataType << endl;
		return -1;
	case GDT_Byte:
		flow_accu<uint8_t >(filename);
		break;
	case GDT_UInt16:
		flow_accu<uint16_t >(filename);
		break;
	case GDT_Int16:
		flow_accu<int16_t >(filename);
		break;
	case GDT_UInt32:
		flow_accu<uint32_t >(filename);
		break;
	case GDT_Int32:
		flow_accu<int32_t >(filename);
		break;
	case GDT_Float32:
		flow_accu<float >(filename);
		break;
	case GDT_Float64:
		flow_accu<double >(filename);
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

//识别嵌套洼地

int __stdcall identify_nested_depressions_alg(char *filename_char){
	const string filename(filename_char);
	GDALDataType dataType = getGDALType(filename);

	switch (dataType) {
	case GDT_Unknown:
		cerr << "Unrecognised data type: " << dataType << endl;
		return -1;
	case GDT_Byte:
		identify_nested_depressions<uint8_t >(filename);
		break;
	case GDT_UInt16:
		identify_nested_depressions<uint16_t >(filename);
		break;
	case GDT_Int16:
		identify_nested_depressions<int16_t >(filename);
		break;
	case GDT_UInt32:
		identify_nested_depressions<uint32_t >(filename);
		break;
	case GDT_Int32:
		identify_nested_depressions<int32_t >(filename);
		break;
	case GDT_Float32:
		identify_nested_depressions<float >(filename);
		break;
	case GDT_Float64:
		identify_nested_depressions<double >(filename);
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

