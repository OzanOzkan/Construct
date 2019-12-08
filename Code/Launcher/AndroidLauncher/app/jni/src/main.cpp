/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and, strings

#include <dlfcn.h>
#include <System/ISystem.h>
#include <SDL.h>

int main( int argc, char* args[] )
{
    std::string nativeLibDir = std::string(args[1]);
    std::string systemLib = nativeLibDir + "/libBokSystem.so";

    auto lib = dlopen(systemLib.c_str(), RTLD_LAZY);

    if (!lib) {
        SDL_Log("%s", dlerror());
    }

    typedef void (*func_ptr_t)(const std::string&);
    func_ptr_t fptr = (func_ptr_t)dlsym(lib, "CreateSystemInterface");
    fptr(nativeLibDir);

    SDL_Log("MAIN FUNCTION END");
	return 0;
}
