#include "stdafx.h"
#include "GameInstance.h"
#include <Windows.h>

#ifdef _DEBUG
/**
 * @brief Entry point for the game in debug mode.
 *
 * This function is executed when the program is compiled in debug mode. It creates an instance of
 * the `GameInstance` class and calls its `Run()` method to start the game. The game loop will run
 * until the game ends. This function will return 0 upon successful completion.
 *
 * @return int Returns 0 if the game runs successfully.
 */
int main()
{
	GameInstance instance; ///< Create a new instance of the game.
	instance.Run();        ///< Start the game loop.
	return 0;              ///< Return 0 to indicate successful execution.
}
int main()
{
	GameInstance instance;
	instance.Run();
	return 0;
}
#else
/**
 * @brief Entry point for the game in release mode.
 *
 * This function is executed when the program is compiled in release mode. It uses the Windows
 * `WinMain` entry point and hides the console window. It creates an instance of the `GameInstance`
 * class and calls its `Run()` method to start the game. The game loop runs until the game ends.
 * The function returns 0 upon successful completion.
 *
 *
 * @return int Returns 0 if the game runs successfully.
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameInstance instance; ///< Create a new instance of the game.
	instance.Run();        ///< Start the game loop.
	return 0;              ///< Return 0 to indicate successful execution.
}
#endif

