#ifndef TOOLMETHOD_
#define TOOLMETHOD_

#include <iostream>
#include <gdal_priv.h>

using namespace std;

GDALDataType getGDALType(const string &filename)
{
	GDALAllRegister();
	GDALDataset *fin = (GDALDataset*)GDALOpen(filename.c_str(), GA_ReadOnly);
	if (fin == NULL)
		throw runtime_error("Unable to read file " + filename + "!");
	GDALRasterBand *band = fin->GetRasterBand(1);
	GDALDataType data_type = band->GetRasterDataType();
	GDALClose(fin);
	return data_type;
}

template<class T>
void getGDALHeader(const string &filename, int32_t &height, int32_t &width, T &no_data, double geotransform[6])
{
	GDALAllRegister();
	GDALDataset *fin = (GDALDataset*)GDALOpen(filename.c_str(), GA_ReadOnly);
	if (fin == NULL)
		throw runtime_error("Unable to read file " + filename + "!");
	GDALRasterBand *band = fin->GetRasterBand(1);
	height = band->GetYSize();
	width = band->GetXSize();
	no_data = band->GetNoDataValue();
	fin->GetGeoTransform(geotransform);
	GDALClose(fin);
}

template<class T>
GDALDataType NativeTypeToGDAL() {
	if (typeid(T) == typeid(uint8_t))
		return GDT_Byte;
	else if (typeid(T) == typeid(uint16_t))
		return GDT_UInt16;
	else if (typeid(T) == typeid(int16_t))
		return GDT_Int16;
	else if (typeid(T) == typeid(uint32_t))
		return GDT_UInt32;
	else if (typeid(T) == typeid(int32_t))
		return GDT_Int32;
	else if (typeid(T) == typeid(float))
		return GDT_Float32;
	else if (typeid(T) == typeid(double))
		return GDT_Float64;
	else {
		cerr << "Could not map native type '" << typeid(T).name() << "' to GDAL type! (Use `c++filt -t` to decode.)" << endl;
		throw runtime_error("Could not map native data type to GDAL type!");
	}
	return GDT_Unknown;
}
#endif
