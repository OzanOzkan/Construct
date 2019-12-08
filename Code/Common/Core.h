/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

// External Library Support

// TODO: Multiplatform support.

#ifdef _WIN32
#define WIN_EXPORT
#include <Windows.h>
#define LoadExternalLibrary(libname) :: LoadLibrary(libname)

# ifdef WIN_EXPORT
#   define API_EXPORT  __declspec( dllexport )
# else
#   define API_IMPORT  __declspec( dllimport )
# endif
#else
#include <dlfcn.h>
# define API_EXPORT
#define LoadExternalLibrary(libname) :: dlopen(libname, RTLD_LAZY)
#define GetProc(handle, func) :: dlsym(handle, func)
#endif

// ~External Library Support