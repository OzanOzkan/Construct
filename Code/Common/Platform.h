#pragma once

//#include <Windows.h>
// External Library Support
//// TODO: Multiplatform support.
//#define EXTERN_LIBRARY_EXPORT __declspec(dllexport)
//#define EXTERN_LIBRARY_IMPORT __declspec(dllimport)
//
//#define LoadExternalLibrary(libname) :: LoadLibrary(libname)
//// ~External Library Support

// Global Environment Variable
//struct SGlobalEnvironment* gEnv = nullptr;

#include "ISystem.h"
struct SGlobalEnvironment* gEnv = nullptr;