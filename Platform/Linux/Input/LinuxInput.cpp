#include "LinuxInput.h"

#include "MPE/MPEPCH.h"
#include "MPE/App/App.h"

#include <GLFW/glfw3.h>

namespace MPE
{
REF<Input> Input::m_inputInstance = NEWREF<LinuxInput>();

bool LinuxInput::IsKeyPressedImpl(int keycode)
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool LinuxInput::IsMouseButtonPressedImpl(int button)
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> LinuxInput::GetMousePositionImpl()
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return {(float) xpos, (float) ypos};
}

float LinuxInput::GetMouseXImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return x;
}

float LinuxInput::GetMouseYImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return y;
}
}