#include "MPE/MPE.h"

#include "MPE/EntryPoint.h"

// TEMP
#include "MPE/Platform/OpenGL/Shaders/OpenGLShader.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"
#include "MPE/Renderer/RendererUtilities.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <opencv2/opencv.hpp>

class OpenCVTestGuiLayer : public MPE::Layer
{
  public:
    OpenCVTestGuiLayer() : Layer("OpenCVTestGuiLayer") {}

    void OnAttach() override {}

    void OnDetach() override {}

    void OnUpdate(MPE::Time deltaTime) override { RenderClearColorScene(); }

    void OnImGuiRender() override
    {

        ImGui::Begin("OpenCV Test", nullptr, ImGuiWindowFlags_NoSavedSettings);

        if(ImGui::Button("Inspect Image"))
        {
            InspectImage();
        }

        ImGui::End();
    }

    void OnEvent(MPE::Event& event) override {}

  private:
    void RenderClearColorScene() { m_RendererUtilities.DrawClearColorScene(); }

    void InspectImage()
    {
        // Load an image from file
        cv::Mat image = cv::imread("Data/OpenCV/example.png");

        // Check if the image file was loaded successfully
        if (image.empty())
        {
            MPE_ERROR("Could not open or find the image");
            return;
        }

        // Display the image in a window
        cv::imshow("Display window", image);

        // Wait for a keystroke in the window
        cv::waitKey(0);
    }

    MPE::RendererUtilities m_RendererUtilities = MPE::RendererUtilities();

    bool m_ShowDemoWindow = false;
};

class OpenCVTest : public MPE::App
{
  public:
    OpenCVTest()
    {
#ifdef MPE_DYNAMIC_LIBRARY
        ImGui::SetCurrentContext(this->GetImGuiContext());
#endif
        // PushLayer(MPE::NEWREF<MainMenuLayer>());
        PushOverlay(MPE::NEWREF<OpenCVTestGuiLayer>());
    }

    ~OpenCVTest() {}
};

MPE::App* MPE::CreateApp()
{
    return new OpenCVTest();
}