#pragma once

// External Library Support

#include <Windows.h>
// TODO: Multiplatform support.
#define API_EXPORT __declspec(dllexport)
#define API_INPORT __declspec(dllimport)

#define LoadExternalLibrary(libname) :: LoadLibrary(libname)
// ~External Library Support

#include "System/ISystem.h"