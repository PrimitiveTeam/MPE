#include "MPE/MPE.h"

#include "MPE/EntryPoint.h"

// TEMP
#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#    include "Platform/OpenGL/Editor/Utilities/OpenGLDebugGuiLayer.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#    include "Platform/OpenGLES/Editor/Utilities/OpenGLESDebugGuiLayer.h"
#endif
#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#include <imgui.h>
#include "MPE/Vendor/GLM/GLM.h"

#include "Tests/ClearColorTest.h"
#include "Tests/SimpleTriangleTest.h"
#include "Tests/SimpleRectangleTest.h"
#include "Tests/ColorTriangleTest.h"
#include "Tests/ColorAnimationTriangleTest.h"
#include "Tests/TextureRectangleTest.h"
#include "Tests/TriangleTransformationTest.h"
#include "Tests/RectangleTransformationTest.h"
#include "Tests/SimpleCubeTest.h"
#include "Tests/TexturesTest.h"
#include "Tests/GeneralTest.h"
#include "Tests/GridTest.h"
#include "Tests/NativeTextTest.h"
#include "Tests/SimpleAudioTest.h"
#include "Tests/SimplePerspectiveCameraTest.h"
#include "Tests/SimpleLightingTest.h"
#include "Tests/SimpleEcsTest.h"
#include "Tests/CubeAbstractionTest.h"
#include "Tests/MultiCubeTest.h"
#include "Tests/SceneTest.h"
#include "Tests/ObjectHierarchyTest.h"
#include "Tests/PropertyViewerTest.h"

class ProjectPickerGuiLayer : public MPE::Layer
{
  public:
    ProjectPickerGuiLayer() : Layer("ProjectPickerGuiLayer")  //, m_OpenGLUtilities(MPE::OpenGLUtilities::getInstance())
    {
    }

    void OnAttach() override {}

    void OnDetach() override {}

    void OnUpdate(MPE::Time deltaTime) override { RenderClearColorScene(); }

    void OnImGuiRender() override
    {
        // PrintLayerStatus();

        ImGui::Begin("Scene Selection", nullptr, ImGuiWindowFlags_NoSavedSettings);

        SceneControl();

        // Add more buttons for other layers here

        ImGui::End();
    }

    void OnEvent(MPE::Event& event) override {}

  private:
    void SceneControl()
    {
        // If any layer is active then we only want to show the close button
        if (std::any_of(m_Layers.begin(), m_Layers.end(), [](bool layer) { return layer; }))
        {
            if (ImGui::Button("Close Layer"))
            {
                for (int i = 0; i < m_Layers.size(); i++)
                {
                    if (m_Layers[i])
                    {
                        m_Layers[i] = false;
                        MPE::App::GetApp().PopLayer(m_LayerRefs[i]);
                        m_LayerRefs[i] = nullptr;
                    }
                }
            }
        }
        else
        {
            if (ImGui::Button("Open Clear Color Test"))
            {
                m_Layers[0] = true;
                m_LayerRefs[0] = MPE::NEWREF<ClearColorTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[0]);
            }

            if (ImGui::Button("Open Simple Triangle Test"))
            {
                m_Layers[1] = true;
                m_LayerRefs[1] = MPE::NEWREF<SimpleTriangleTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[1]);
            }

            if (ImGui::Button("Open Simple Rectangle Test"))
            {
                m_Layers[2] = true;
                m_LayerRefs[2] = MPE::NEWREF<SimpleRectangleTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[2]);
            }

            if (ImGui::Button("Open Color Triangle Test"))
            {
                m_Layers[3] = true;
                m_LayerRefs[3] = MPE::NEWREF<ColorTriangleTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[3]);
            }

            if (ImGui::Button("Open Color Animation Triangle Test"))
            {
                m_Layers[4] = true;
                m_LayerRefs[4] = MPE::NEWREF<ColorAnimationTriangleTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[4]);
            }

            if (ImGui::Button("Open Texture Rectangle Test"))
            {
                m_Layers[5] = true;
                m_LayerRefs[5] = MPE::NEWREF<TextureRectangleTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[5]);
            }

            if (ImGui::Button("Open Triangle Transformation Test"))
            {
                m_Layers[6] = true;
                m_LayerRefs[6] = MPE::NEWREF<TriangleTransformationTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[6]);
            }

            if (ImGui::Button("Open Rectangle Transformation Test"))
            {
                m_Layers[7] = true;
                m_LayerRefs[7] = MPE::NEWREF<RectangleTransformationTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[7]);
            }

            if (ImGui::Button("Open Simple Cube Test"))
            {
                m_Layers[8] = true;
                m_LayerRefs[8] = MPE::NEWREF<SimpleCubeTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[8]);
            }

            if (ImGui::Button("Open Grid Test"))
            {
                m_Layers[9] = true;
                m_LayerRefs[9] = MPE::NEWREF<GridTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[9]);
            }

            if (ImGui::Button("Open Native Text Test"))
            {
                m_Layers[10] = true;
                m_LayerRefs[10] = MPE::NEWREF<NativeTextTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[10]);
            }

            if (ImGui::Button("Open Simple Audio Test"))
            {
                m_Layers[11] = true;
                m_LayerRefs[11] = MPE::NEWREF<SimpleAudioTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[11]);
            }

            if (ImGui::Button("Open Simple Perspective Camera Test"))
            {
                m_Layers[12] = true;
                m_LayerRefs[12] = MPE::NEWREF<SimplePerspectiveCameraTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[12]);
            }

            if (ImGui::Button("Open Simple Lighting Test"))
            {
                m_Layers[13] = true;
                m_LayerRefs[13] = MPE::NEWREF<SimpleLightingTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[13]);
            }

            if (ImGui::Button("Open Simple ECS Test"))
            {
                m_Layers[14] = true;
                m_LayerRefs[14] = MPE::NEWREF<SimpleEcsTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[14]);
            }

            if (ImGui::Button("Open Cube Abstraction Test"))
            {
                m_Layers[15] = true;
                m_LayerRefs[15] = MPE::NEWREF<CubeAbstractionTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[15]);
            }

            if (ImGui::Button("Open Multi Cube Test"))
            {
                m_Layers[16] = true;
                m_LayerRefs[16] = MPE::NEWREF<MultiCubeTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[16]);
            }

            if (ImGui::Button("Open Scene Test"))
            {
                m_Layers[17] = true;
                m_LayerRefs[17] = MPE::NEWREF<SceneTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[17]);
            }

            if (ImGui::Button("Open Object Hierarchy Test"))
            {
                m_Layers[18] = true;
                m_LayerRefs[18] = MPE::NEWREF<ObjectHierarchyTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[18]);
            }

            if (ImGui::Button("Open Property Viewer Test"))
            {
                m_Layers[19] = true;
                m_LayerRefs[19] = MPE::NEWREF<PropertyViewerTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[19]);
            }

            // if (ImGui::Button("Open General Layer"))
            // {
            //     m_Layers[1] = true;
            //     m_LayerRefs[1] = MPE::NEWREF<GeneralTest>();
            //     MPE::App::GetApp().PushLayer(m_LayerRefs[0]);
            // }

            // if (ImGui::Button("Open Textures Layer"))
            // {
            //     m_Layers[2] = true;
            //     m_LayerRefs[2] = MPE::NEWREF<TexturesTest>();
            //     MPE::App::GetApp().PushLayer(m_LayerRefs[1]);
            // }
        }
    }

    void RenderClearColorScene()
    {
        // If any layer is active, do not execute this
        if (std::any_of(m_Layers.begin(), m_Layers.end(), [](bool layer) { return layer; })) return;

        m_RendererUtilities.DrawClearColorScene();
    }

    void PrintLayerStatus()
    {
        // Using array
        // MPE_CORE_INFO("General Layer: {0}", m_Layers[0] ? "true" : "false");
        // MPE_CORE_INFO("Textures Layer: {0}", m_Layers[1] ? "true" : "false");
    }

  private:
    static const size_t MAX_LAYERS = 20;
    std::array<bool, MAX_LAYERS> m_Layers = {false};
    MPE::REF<MPE::Layer> m_LayerRefs[MAX_LAYERS];
    MPE::RendererUtilities m_RendererUtilities = MPE::RendererUtilities();
};

class ProjectPicker : public MPE::App
{
  public:
    ProjectPicker()
    {
#ifdef MPE_DYNAMIC_LIBRARY
        ImGui::SetCurrentContext(this->GetImGuiContext());
#endif
// PushLayer(MPE::NEWREF<MainMenuLayer>());
#ifdef MPE_OPENGL
        PushLayer(MPE::NEWREF<MPE::OpenGLDebugGuiLayer>());
#elif MPE_OPENGLES
        PushLayer(MPE::NEWREF<MPE::OpenGLESDebugGuiLayer>());
#endif
        PushOverlay(MPE::NEWREF<ProjectPickerGuiLayer>());
    }

    ~ProjectPicker() {}
};

MPE::App* MPE::CreateApp()
{
    return new ProjectPicker();
}