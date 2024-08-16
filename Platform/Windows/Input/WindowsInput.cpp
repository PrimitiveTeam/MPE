#include "WindowsInput.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_PTRS.h"
#include "MPE/App/App.h"
#include "MPE/Input/KeyState.h"

#include <GLFW/glfw3.h>

namespace MPE
{
REF<Input> Input::m_inputInstance = NEWREF<WindowsInput>();

bool WindowsInput::IsKeyPressedImpl(int keycode)
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    bool isPressed = state == GLFW_PRESS || state == GLFW_REPEAT;
    MPE::KeyState::SetKeyPressed(keycode, isPressed);
    return isPressed;
}

bool WindowsInput::IsMouseButtonPressedImpl(int button)
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::GetMousePositionImpl()
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return {(float) xpos, (float) ypos};
}

float WindowsInput::GetMouseXImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return x;
}

float WindowsInput::GetMouseYImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return y;
}
}