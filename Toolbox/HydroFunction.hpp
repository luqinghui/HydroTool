#pragma once
#include <gdal_priv.h>
#include <iostream>

#include "ToolMethod.hpp"
#include "ArrayDEM.hpp"
#include "Depressions.hpp"
#include "FlowDirection.hpp"
#include "FlowAccumulation.hpp"


extern "C"
{
	__declspec(dllexport) int __stdcall flow_dir_pf_d8_alg(char *filename_char, bool forceout);
	__declspec(dllexport) int __stdcall flow_dir_original_d8_alg(char *filename_char, bool forceout);
	__declspec(dllexport) int __stdcall fill_depression_alg(char *filename_char);
	__declspec(dllexport) int __stdcall identify_depression_alg(char *filename_char);
	__declspec(dllexport) int __stdcall flow_accu_alg(char *filename_char);
	__declspec(dllexport) int __stdcall identify_nested_depressions_alg(char *filename_char);
}


