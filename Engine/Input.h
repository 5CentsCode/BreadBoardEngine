#pragma once
#include <queue>
#include <map>
#include "KeyCodes.h"

class Input
{
    friend class Window;

public:

    static bool IsKeyPressed(KeyCode key);
    static bool IsKeyDown(KeyCode key);
    static bool IsKeyReleased(KeyCode key);
    static bool IsKeyUp(KeyCode key);
    static KeyCode GetKeyPressed(void);
    static KeyCode GetCharPressed(void);

    static bool IsMouseButtonPressed(MouseCode button);
    static bool IsMouseButtonDown(MouseCode button);
    static bool IsMouseButtonReleased(MouseCode button);
    static bool IsMouseButtonUp(MouseCode button);

    static glm::vec2 GetMousePosition(void);
    static glm::vec2 GetMouseDelta(void);
    static void SetMousePosition(glm::ivec2 position);

    static glm::vec2 GetScrollWheelMove(void);
    static glm::vec2 GetScrollWheelDelta(void);

    static void PollInputEvents(void);

private:

    static void KeyCallback(struct GLFWwindow* glfwWindow, int32 key, int32 scancode, int32 action, int32 mods);
    static void CharCallback(struct GLFWwindow* glfwWindow, uint32 key);
    static void MouseButtonCallback(struct GLFWwindow* glfwWindow, int32 button, int32 action, int32 mods);
    static void MouseCursorPosCallback(struct GLFWwindow* glfwWindow, double x, double y);
    static void MouseScrollCallback(struct GLFWwindow* glfwWindow, double xOffset, double yOffset);
    static void CursorEnterCallback(struct GLFWwindow* glfwWindow, int32 enter);

private:

    struct KeyboardState
    {
        InputState CurrentKeyState[512];
        InputState PreviousKeyState[512];

        std::queue<KeyCode> KeyPressQueue;
        std::queue<KeyCode> CharPressQueue;
    };

    struct MouseState
    {
        glm::vec2 Offset;
        glm::vec2 Scale;
        glm::vec2 CurrentPosition;
        glm::vec2 PreviousPosition;

        InputState CurrentButtonState[8];
        InputState PreviousButtonState[8];

        glm::vec2 CurrentWheelMove;
        glm::vec2 PreviousWheelMove;

        int8 Cursor;
        bool Hidden;
        bool OnScreen;
    };

    static KeyboardState Keyboard;
    static MouseState Mouse;
};