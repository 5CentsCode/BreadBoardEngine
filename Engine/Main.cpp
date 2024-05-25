#include "Application.h"

int main(void)
{
	Application app;

	app.Initialize();

	app.Run();

	app.Shutdown();

	return 0;
}