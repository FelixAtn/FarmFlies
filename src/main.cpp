#include "stdafx.h"
#include "GameInstance.h"

#ifdef _DEBUG
// Debug mode: show console
int main()
{
	GameInstance instance;
	instance.Run();
	return 0;
}
#else
// Release mode: hide console
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameInstance instance;
	instance.Run();
	return 0;
}
#endif

