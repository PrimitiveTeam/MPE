// #include "MPE/MPE.h"

// // TEMP
// #include "MPE/Platform/OpenGL/Shaders/OpenGLShader.h"
// #include "MPE/Renderer/Shaders/ShaderLibrary.h"

// #include <imgui.h>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glad/glad.h>
// // TEMP
// class TestLayer : public MPE::Layer
// {
//   private:
//   public:
//     TestLayer() : Layer("Test") {}

//     virtual void OnUpdate(MPE::Time deltaTime) override {}

//     virtual void OnImGuiRender() override {}

//     virtual void OnEvent(MPE::Event &event) override {}
// };

// class Example : public MPE::App
// {
//   public:
//     Example()
//     {
// #ifdef MPE_DYNAMIC_LIBRARY
//         ImGui::SetCurrentContext(this->GetImGuiContext());
// #endif

//         PushLayer(new TestLayer());
//     }

//     ~Example() {}
// };

// MPE::App *MPE::CreateApp()
// {
//     return new Example();
// }