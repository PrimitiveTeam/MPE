#include "macOSInput.h"

#include "MPE/MPEPCH.h"
#include "MPE/App/App.h"

#include <GLFW/glfw3.h>

namespace MPE
{
REF<Input> Input::SYS_Input_Instance = NEWREF<macOSInput>();

bool macOSInput::IsKeyPressedImpl(int keycode)
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool macOSInput::IsMouseButtonPressedImpl(int button)
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> macOSInput::GetMousePositionImpl()
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return {(float) xpos, (float) ypos};
}

float macOSInput::GetMouseXImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return x;
}

float macOSInput::GetMouseYImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return y;
}
}