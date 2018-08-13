#pragma region project include
#include "Engine.h"
#include "Config.h"
#pragma endregion

/// <summary>
/// entry point of application
/// </summary>
/// <param name="argc">count of parameter</param>
/// <param name="argv">parameter</param>
/// <returns>code of shut down</returns>
int main(int argc, char* argv[])
{
	// load config
	GConfig::SetValues();

	// init engine and load images
	if (CEngine::Get()->Init() && CEngine::Get()->Load())
	{
		// run engine
		CEngine::Get()->Run();
	}

	// not initialized or loaded
	else
	{
		return 1;
	}

	// clean engine
	CEngine::Get()->Clean();

	// shutdown correctly
	return 0;
}