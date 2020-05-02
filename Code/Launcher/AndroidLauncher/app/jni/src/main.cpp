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

    typedef ISystem* (*func_ptr_t)();
    auto fptr = (func_ptr_t)dlsym(lib, "CreateSystemInterface");
    fptr()->InitializeModule();

    SDL_Log("MAIN FUNCTION END");
	return 0;
}
