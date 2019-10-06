/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

// External Library Support
#include <Windows.h>
// TODO: Multiplatform support.
#define API_EXPORT __declspec(dllexport)
#define API_IMPORT __declspec(dllimport)

#define LoadExternalLibrary(libname) :: LoadLibrary(libname)
// ~External Library Support