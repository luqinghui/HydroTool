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
	string fullname;
	string basename;
	string dir;
	string filename;
	string ext;
	vector<double> geotransform;
	string projection;

	ArrayDEM(const string &infile)
	{
		fullname = infile;
		basename = fullname.substr(fullname.find_last_of('\\') + 1);
		dir = fullname.substr(0, fullname.find_last_of('\\'));
		ext = fullname.substr(fullname.find_last_of('.')+1);
		filename = basename.substr(0, basename.find_last_of('.'));
		loadGDAL();
	}

	ArrayDEM()
	{

	}

	template<class U>
	void resize(ArrayDEM<U> &other, const T& val = T()) {
		resize(other.width(), other.height(), val);
		geotransform = other.geotransform;
		projection = other.projection;
	}

	void resize(xy_t width, xy_t height, const T& val = T()) {
		data.resize(width*height);
		fill(data.begin(), data.end(), val);
		view_height = height;
		view_width = width;
	}
	
	T& operator()(xy_t x, xy_t y) {
		return data[xyToI(x, y)];
	}
	T operator()(xy_t x, xy_t y) const {
		return data[xyToI(x, y)];
	}


	T* getData()
	{
		return data.data();
	}

	xy_t width()
	{
		return view_width;
	}
	xy_t height()
	{
		return view_height;
	}

	T getNoData()
	{
		return no_data;
	}

	void setNoData(T val)
	{
		no_data = val;
	}

	bool inGrid(xy_t x, xy_t y)
	{
		return (0 <= x && x < view_width && 0 <= y && y < view_height);
	}

	bool isEdge(xy_t x, xy_t y)
	{
		for (int i = 0; i < 8; i++)
		{
			xy_t nx = x + dx[i];
			xy_t ny = y + dy[i];
			if (!inGrid(nx, ny) || (data[xyToI(nx, ny)] == no_data))
				return true;
		}
		return false;
	}

	void saveGDAL(const string &filename)
	{
		GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
		if (poDriver == NULL)
		{
			cerr << "Could not open GDAL driver!" << endl;
			throw runtime_error("Could not open GDAL driver!");
		}
		GDALDataset *fout = poDriver->Create(filename.c_str(), view_width, view_height, 1, myGDALType(), NULL);
		if (fout == NULL)
		{
			cerr << "Could not create GDAL save file:" << filename << "!" << endl;
			throw runtime_error("Could not create save file!");
		}
		GDALRasterBand *poBand = fout->GetRasterBand(1);
		poBand->SetNoDataValue(no_data);

		fout->SetGeoTransform(geotransform.data());

		fout->SetProjection(projection.c_str());
		auto temp = poBand->RasterIO(GF_Write, 0, 0, view_width, view_height, data.data(), view_width, view_height, myGDALType(), 0, 0);

		if (temp != CE_None)
			cerr << "Error writing file!" << endl;
		GDALClose(fout);
	}

	void saveGDAL(const string &filename, GDALDataType type) {
		GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
		if (poDriver == NULL) {
			cerr << "Could not open GDAL driver!" << endl;
			throw runtime_error("Could not open GDAL driver!");
		}
		GDALDataset *fout = poDriver->Create(filename.c_str(), view_width, view_height, 1, type, NULL);
		if (fout == NULL) {
			cerr << "Could not create GDAL save file:" << filename << "!" << endl;
			throw runtime_error("Could not create save file!");
		}
		GDALRasterBand *poBand = fout->GetRasterBand(1);
		poBand->SetNoDataValue(no_data);

		fout->SetGeoTransform(geotransform.data());

		fout->SetProjection(projection.c_str());
		auto temp = poBand->RasterIO(GF_Write, 0, 0, view_width, view_height, data.data(), view_width, view_height, type, 0, 0);

		if (temp != CE_None)
			cerr << "Error writing file!" << endl;
		GDALClose(fout);
	}

	

	void printStamp()
	{
		cout << "projection:" << projection << endl;
		cout << "geotransform:" << endl;
		for (auto iter = geotransform.cbegin(); iter != geotransform.cend(); iter++)
		{
			cout << *iter << endl;
		}
		cout << "width:" << view_width << endl;
		cout << "height:" << view_height << endl;
		cout << "fullpath:" << fullname << endl;
		cout << "basename:" << basename << endl;
	}

private:
	vector<T> data;
	T no_data;
	xy_t view_width;
	xy_t view_height;

	i_t xyToI(xy_t x, xy_t y)
	{
		return (i_t)y*(i_t)view_width + (i_t)x;
	}

	GDALDataType myGDALType() const
	{
		return NativeTypeToGDAL<T>();
	}
	void loadGDAL()
	{
		GDALAllRegister();
		GDALDataset *fin = (GDALDataset*)GDALOpen(fullname.c_str(), GA_ReadOnly);
		if (fin == NULL)
			throw runtime_error("Unable to read file " + fullname + "!");
		GDALRasterBand *band = fin->GetRasterBand(1);
		view_height = band->GetYSize();
		view_width = band->GetXSize();
		no_data = band->GetNoDataValue();
		geotransform.resize(6);
		if (fin->GetGeoTransform(geotransform.data()) != CE_None)
		{
			cerr << "Warning, could not get a geotransform from '" << fullname << "'! Setting to standard geotransform." << endl;
			geotransform = { { 1000., 1., 0., 1000., 0., -1. } };
		}

		const char* projection_string = fin->GetProjectionRef();
		projection = string(projection_string);

		//load data
		data.resize(view_height*view_width);
		auto temp = band->RasterIO(GF_Read, 0, 0, view_width, view_height, data.data(), view_width, view_height, myGDALType(), 0, 0);
		if (temp != CE_None) {
			cerr << "An error occured while trying to read '" << fullname << "' into RAM." << endl;
			throw runtime_error("Error reading file with GDAL!");
		}

		GDALClose(fin);
	}
};
#endif