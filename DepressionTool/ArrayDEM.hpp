#ifndef ARRAYDEM_
#define ARRAYDEM_

#include <iostream>
#include <gdal_priv.h>
#include "Constants.hpp"

using namespace std;

//index
typedef int32_t xy_t;
typedef uint32_t i_t;

template<class T>
class ArrayDEM
{
public:
	string filename;
	string basename;
	vector<double> geotransform;
	string projection;

	ArrayDEM(const string &infile)
	{
		filename = infile;
		basename = filename.substr(filename.find_last_of('\\') + 1);
		loadGDAL();
	}

	ArrayDEM()
	{

	}

	template<class U>
	void resize(const ArrayDEM<U> &other, const T& val = T()) {
		resize(other.width(), other.height(), val);
		geotransform = other.geotransform;
		projection = other.projection;
	}

	
	T& operator()(xy_t x, xy_t y) {
		return data[xyToI(x, y)];
	}
	T operator()(xy_t x, xy_t y) const {
		return data[xyToI(x, y)];
	}


	T* getData(void)
	{
		return data.data();
	}

	xy_t width(void)
	{
		return view_width;
	}
	xy_t height(void)
	{
		return view_height;
	}

	T getNoData(void) const
	{
		return no_data;
	}

	void setNoData(T val)
	{
		no_data = val;
	}

	bool inGrid(xy_t x, xy_t y) const
	{
		return (0 <= x && x < view_width && 0 <= y && y < view_height);
	}

	bool isEdge(xy_t x, xy_t y) const
	{
		for (int i = 1; i <= 8; i++)
		{
			xy_t nx = x + dx[i];
			xy_t ny = y + dy[i];
			if (!inGrid(nx, ny) || (data[xyTol(nx, ny)] == no_data))
				return true;
		}
	}

	void saveGDAL(const string &filename)
	{

	}

	void printStamp(void)
	{
		cout << "projection:" << projection << endl;
		cout << "geotransform:" << endl;
		for (auto iter = geotransform.cbegin(); iter != geotransform.cend(); iter++)
		{
			cout << *iter << endl;
		}
		cout << "width:" << view_width << endl;
		cout << "height:" << view_height << endl;
		cout << "fullpath:" << filename << endl;
		cout << "basename:" << basename << endl;
	}

private:
	vector<T> data;
	T no_data;
	xy_t view_width;
	xy_t view_height;

	i_t xyTol(xy_t x, xy_t y)
	{
		return (i_t)y*(i_t)view_width + (i_t)x;
	}

	void resize(xy_t width, xy_t height, const T& val = T()) {
		data.resize(width*height);
		fill(data.begin(), data.end(), val);
		view_height = height;
		view_width = width;
	}


	GDALDataType myGDALType(void) const
	{
		return NativeTypeToGDAL<T>();
	}
	void loadGDAL()
	{
		GDALAllRegister();
		GDALDataset *fin = (GDALDataset*)GDALOpen(filename.c_str(), GA_ReadOnly);
		if (fin == NULL)
			throw runtime_error("Unable to read file " + filename + "!");
		GDALRasterBand *band = fin->GetRasterBand(1);
		view_height = band->GetYSize();
		view_width = band->GetXSize();
		no_data = band->GetNoDataValue();
		geotransform.resize(6);
		if (fin->GetGeoTransform(geotransform.data()) != CE_None)
		{
			cerr << "Warning, could not get a geotransform from '" << filename << "'! Setting to standard geotransform." << endl;
			geotransform = { { 1000., 1., 0., 1000., 0., -1. } };
		}

		const char* projection_string = fin->GetProjectionRef();
		projection = string(projection_string);

		//load data
		data.resize(view_height*view_width);
		auto temp = band->RasterIO(GF_Read, 0, 0, view_width, view_height, data.data(), view_width, view_height, myGDALType(), 0, 0);
		if (temp != CE_None) {
			cerr << "An error occured while trying to read '" << filename << "' into RAM." << endl;
			throw runtime_error("Error reading file with GDAL!");
		}

		GDALClose(fin);
	}
};
#endif