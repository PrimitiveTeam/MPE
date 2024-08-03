#include "RPIInput.h"

#include "MPE/MPEPCH.h"
#include "MPE/App/App.h"

#include <GLFW/glfw3.h>

namespace MPE
{
REF<Input> Input::SYS_Input_Instance = NEWREF<RPIInput>();

bool RPIInput::IsKeyPressedImpl(int keycode)
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool RPIInput::IsMouseButtonPressedImpl(int button)
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> RPIInput::GetMousePositionImpl()
{
    auto window = static_cast<GLFWwindow *>(App::GetApp().GetWindow()->GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return {(float) xpos, (float) ypos};
}

float RPIInput::GetMouseXImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return x;
}

float RPIInput::GetMouseYImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return y;
}
}