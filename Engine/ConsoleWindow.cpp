#include "ConsoleWindow.h"

#if _DEBUG

#include <iostream>
#include <Windows.h>

ConsoleWindow::ConsoleWindow(uint16 bufferLength)
{
	CreateNewConsole(bufferLength);
}

ConsoleWindow::~ConsoleWindow()
{
	ReleaseConsole();
}

bool ConsoleWindow::CreateNewConsole(uint16 bufferLength)
{
	bool result = false;

	// Release any current console and redirect IO to NUL
	ReleaseConsole();

	// Attempt to create new console
	if (AllocConsole())
	{
		AdjustConsoleBuffer(bufferLength);
		result = RedirectConsoleIO();

		HWND consoleHandle = GetConsoleWindow();
		HMENU hmenu = GetSystemMenu(consoleHandle, FALSE);
		EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
	}
	printf("Console Created\n");

	return result;
}

bool ConsoleWindow::AttachParentConsole(uint16 bufferLength)
{
	bool result = false;

	// Release any current console and redirect IO to NUL
	ReleaseConsole();

	// Attempt to attach to parent process's console
	if (AttachConsole(ATTACH_PARENT_PROCESS))
	{
		AdjustConsoleBuffer(bufferLength);
		result = RedirectConsoleIO();
	}
	printf("Attaching Console");

	return result;
}

void ConsoleWindow::AdjustConsoleBuffer(uint16 bufferLength)
{
	// Set the screen buffer to be big enough to scroll some text
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
	if (conInfo.dwSize.Y < bufferLength)
	{
		conInfo.dwSize.Y = bufferLength;
	}
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
}

bool ConsoleWindow::ReleaseConsole()
{
	bool result = true;
	FILE* fp;

	// Just to be safe, redirect standard IO to NUL before releasing.
	printf("Releasing Console");

	// Redirect STDIN to NUL
	if (freopen_s(&fp, "NUL:", "r", stdin) != 0)
	{
		result = false;
	}
	else
	{
		setvbuf(stdin, NULL, _IONBF, 0);
	}

	// Redirect STDOUT to NUL
	if (freopen_s(&fp, "NUL:", "w", stdout) != 0)
	{
		result = false;
	}
	else
	{
		setvbuf(stdout, NULL, _IONBF, 0);
	}

	// Redirect STDERR to NUL
	if (freopen_s(&fp, "NUL:", "w", stderr) != 0)
	{
		result = false;
	}
	else
	{
		setvbuf(stderr, NULL, _IONBF, 0);
	}

	// Detach from console
	if (!FreeConsole())
	{
		result = false;
	}

	return result;
}

bool ConsoleWindow::RedirectConsoleIO()
{
	bool result = true;
	FILE* fp;

	// Redirect STDIN if the console has an input handle
	if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
	{
		if (freopen_s(&fp, "CONIN$", "r", stdin) != 0)
		{
			result = false;
		}
		else
		{
			setvbuf(stdin, NULL, _IONBF, 0);
		}
	}

	// Redirect STDOUT if the console has an output handle
	if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
		if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0)
		{
			result = false;
		}
		else
		{
			setvbuf(stdout, NULL, _IONBF, 0);
		}

	// Redirect STDERR if the console has an error handle
	if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
	{
		if (freopen_s(&fp, "CONOUT$", "w", stderr) != 0)
		{
			result = false;
		}
		else
		{
			setvbuf(stderr, NULL, _IONBF, 0);
		}
	}

	// Make C++ standard streams point to console as well.
	std::ios::sync_with_stdio(true);

	// Clear the error state for each of the C++ standard streams.
	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();

	return result;
}

#endif