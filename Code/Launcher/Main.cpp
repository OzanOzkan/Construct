/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup").

#include <direct.h>
#define GetCurrentDir _getcwd

#include <iostream>

#include <Windows.h>
#define LoadExternalLibrary(libname) :: LoadLibrary(libname)

#include <System/ISystem.h>

int main()
{
	// Working dir
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	std::cout << "Dir: " << current_working_dir.c_str() << std::endl;
	//~Working dir

	auto lib = LoadExternalLibrary("System.dll");
	typedef ISystem*(*FNPTR)();
	FNPTR CreateSystemInterface = (FNPTR)GetProcAddress(lib, "CreateSystemInterface");

	if (!CreateSystemInterface) {
		std::cout << "Cannot find System.dll" << std::endl;
	}
	else
	{
		if (ISystem* pSystem = CreateSystemInterface())
		{
			pSystem->InitializeModule();
		}

	}

	std::cout << "End of program." << std::endl;
	std::getchar();

	return EXIT_SUCCESS;
}