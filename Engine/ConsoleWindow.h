#pragma once

#if _DEBUG

#include "Typedefs.h"

class ConsoleWindow
{
public:
	ConsoleWindow(uint16 bufferLength = 2048);
	~ConsoleWindow();

public:
	static bool CreateNewConsole(uint16 bufferLength = 2048);
	static bool AttachParentConsole(uint16 bufferLength = 2048);
	static void AdjustConsoleBuffer(uint16 bufferLength);
	static bool ReleaseConsole();

private:
	static bool RedirectConsoleIO();
};

#endif