#include "System.h"
#include "IPlatform.h"

#include <memory>

EXTERN_DLL_EXPORT ISystem* CreateSystem() {

	std::unique_ptr<CSystem> pSystem = std::make_unique<CSystem>();
	
	return pSystem.release();
}
