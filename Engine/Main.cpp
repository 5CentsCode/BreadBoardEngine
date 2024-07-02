#include "Application.h"

#if _DEBUG
#include "ConsoleWindow.h"
#endif


int main(void)
{
#if _DEBUG
	ConsoleWindow::CreateNewConsole();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif

	std::unique_ptr<Application> app = CreateApplication();

	app->InternalInitialize();
	app->InternalRun();
	app->InternalShutdown();

	app.reset();

#if _DEBUG
	ConsoleWindow::ReleaseConsole();
#endif

	return 0;
}