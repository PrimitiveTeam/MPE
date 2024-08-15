#include "NativeTextTest.h"
#include "MPE/MPEPCH.h"

#include <glm/gtc/matrix_transform.hpp>

#ifdef MPE_OPENGL
#    include "MPE/MPEGFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPEGFX_OPEN_GL_ES.h"
#endif

NativeTextTest::NativeTextTest()
    : Layer("Test"),
      CLEAR_COLOR{0.5f, 0.25f, 0.5f},
      SYS_CAMERA_CONTROLLER(1280.0f / 720.0f, true),
      TEXT_COLOR{0.88f, 0.59f, 0.07f, 0.75f},
      TEXT_SCALE(1.0f),
      TEXT_BOX_LOCATION{0.0f, 0.0f},
      SYS_TEXT_RENDERER("Data/Shaders/Text/Text.glsl", "Data/Fonts/Hack_v3_003/Hack-Regular.ttf", 64, &SYS_CAMERA_CONTROLLER.GetCamera())
{
    // SYS_TEXT_RENDERER = MPE::OpenGLTextRenderer("Data/Shaders/Text/Text.glsl", "Data/Fonts/Hack_v3_003/Hack-Regular.ttf", 64,
    // &SYS_CAMERA_CONTROLLER.GetCamera());
    TEXT = "Hello World!";
}

void NativeTextTest::OnUpdate(MPE::Time deltaTime)
{
    SYS_CAMERA_CONTROLLER.OnUpdate(deltaTime);

    MPE::RenderPrimitive::SetClearColor(glm::vec4(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]));
    MPE::RenderPrimitive::Clear();

    // MPE::Renderer::BeginScene(SYS_CAMERA_CONTROLLER.GetCamera());

    SYS_TEXT_RENDERER.RenderText(TEXT, TEXT_BOX_LOCATION[0], TEXT_BOX_LOCATION[1], TEXT_SCALE,
                                 glm::vec4(TEXT_COLOR[0], TEXT_COLOR[1], TEXT_COLOR[2], TEXT_COLOR[3]));
    SYS_TEXT_RENDERER.RenderAllASCII(500.0f, 500.0f, 1.0f, glm::vec4(0.88f, 0.59f, 0.07f, 1.0f));

    // MPE::Renderer::EndScene();
}

void NativeTextTest::OnImGuiRender()
{
    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", CLEAR_COLOR);

    ImGui::Separator();

    ImGui::Text("TEXT VARIABLES");

    static char buffer[256];
    strncpy(buffer, TEXT.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = 0;

    if (ImGui::InputText("TEXT", buffer, sizeof(buffer)))
    {
        TEXT = std::string(buffer);
    }

    ImGui::ColorEdit4("TEXT COLOR", TEXT_COLOR);
    ImGui::SliderFloat("TEXT SCALE", &TEXT_SCALE, 0.0f, 5.0f);
    if (ImGui::Button("Reset Text Scale")) TEXT_SCALE = 1.0f;
    ImGui::SliderFloat("[X] TEXT BOX LOCATION", &TEXT_BOX_LOCATION[0], 0.0f, 1280.0f);
    ImGui::SliderFloat("[Y] TEXT BOX LOCATION", &TEXT_BOX_LOCATION[1], 0.0f, 720.0f);

    bool pixelAlign = SYS_TEXT_RENDERER.GetPixelAlign();
    ImGui::Checkbox("Pixel Align", &pixelAlign);
    SYS_TEXT_RENDERER.SetPixelAlign(pixelAlign);

    int fontSize = SYS_TEXT_RENDERER.GetFontSize();
    ImGui::SliderInt("Font Size", &fontSize, 1.0, 128.0);
    SYS_TEXT_RENDERER.SetFontSize(fontSize);

    ImGui::End();
}

void NativeTextTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(NativeTextTest::OnKeyPressedEvent));

    SYS_CAMERA_CONTROLLER.OnEvent(event);
    SYS_TEXT_RENDERER.OnEvent(event);
}

bool NativeTextTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}