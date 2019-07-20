#include <iostream>

#include <Windows.h>
#define LoadExternalLibrary(libname) :: LoadLibrary(libname)

#include <ISystem.h>

int main()
{
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

	return EXIT_SUCCESS;
}