#pragma once
#include "Typedefs.h"

class Window
{
public:

	Window() : Window(800, 600, "Window") {}
	Window(int32 width, int32 height, const char* title);
	~Window();

	bool ShouldClose() const;

	bool IsMinimized() const;
	bool IsMaximized() const;
	bool IsFullScreen() const;

	int32 GetWidth() const;
	int32 GetHeight() const;
	glm::ivec2 GetSize() const;
	float GetAspectRatio() const;

	glm::ivec2 GetPosition() const;

	void* GetHandle() const;

public:

	void Close();

	void ToggleFullscreen();
	void Maximise();
	void Minimize();
	void Restore();

	void SetTitle(const char* title);

	void SetPosition(int32 x, int32 y);
	void SetPosition(glm::ivec2 position);
	void SetWindowMonitor(uint8 monitor);

	void SetSize(int32 width, int32 height);
	void SetSize(glm::ivec2 size);

private:

	static void PositionCallback(struct GLFWwindow* glfwWindow, int32 x, int32 y);
	static void SizeCallback(struct GLFWwindow* glfwWindow, int32 width, int32 heigt);
	static void MaximizeCallback(struct GLFWwindow* glfwWindow, int32 maximized);
	static void MinimizeCallback(struct GLFWwindow* glfwWindow, int32 minimized);
	static void FocusCallback(struct GLFWwindow* glfwWindow, int32 focused);
	static void DropCallback(struct GLFWwindow* glfwWindow, int32 count, const char** paths);

private:

	struct GLFWwindow* m_window;
};