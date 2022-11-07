#include <Windows.h>
#include <crtdbg.h>
#include "../../../include/EngineMain/EngineMain.hpp"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	{
		gnMain();
	}

	return 0;
}