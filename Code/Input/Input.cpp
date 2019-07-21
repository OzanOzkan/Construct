#include "Input.h"

#include <ILog.h>

#include <memory>

extern "C"
{
	EXTERN_LIBRARY_EXPORT IInput* CreateInputInterface(SEnvironment *env)
	{
		std::unique_ptr<CInput> pInput = std::make_unique<CInput>(env);

		return pInput.release();
	}
}

CInput::CInput(SEnvironment* env)
	:m_pEnv(env)
{

}

CInput::~CInput()
{

}

void CInput::InitializeModule()
{

}

void CInput::Update()
{
}

void CInput::IsKeyPressed()
{

}
