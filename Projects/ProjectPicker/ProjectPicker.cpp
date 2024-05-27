#include "MPE/MPE.h"

#include "MPE/EntryPoint.h"

// TEMP
#include "MPE/Platform/OpenGL/Shaders/OpenGLShader.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"
#include "MPE/Renderer/RendererUtilities.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Tests/TexturesTestLayer.h"
#include "Tests/GeneralTestLayer.h"

class ProjectPickerGuiLayer : public MPE::Layer
{
  public:
    ProjectPickerGuiLayer() : Layer("ProjectPickerGuiLayer") {}

    void OnAttach() override {}

    void OnDetach() override {}

    void OnUpdate(MPE::Time deltaTime) override { RenderClearColorScene(); }

    void OnImGuiRender() override
    {
        // PrintLayerStatus();

        ImGui::Begin("Main Menu");

        GuiButtons();

        DisplayRefs();

        // Add more buttons for other layers here

        ImGui::End();
    }

    void OnEvent(MPE::Event& event) override {}

  private:
    void DisplayRefs()
    {
        ImGui::Text("Total References: %d", MPE::ReferenceTracker::getInstance().GetTotalReferences());

        if (ImGui::BeginListBox("References"))
        {
            auto refs = MPE::ReferenceTracker::getInstance().GetReferences();
            for (const auto& ref : refs)
            {
                ImGui::Text(ref.c_str());
            }
            ImGui::EndListBox();
        }

        if (ImGui::BeginListBox("Scope References"))
        {
            auto refs = MPE::ReferenceTracker::getInstance().GetScopeReferences();
            for (const auto& ref : refs)
            {
                ImGui::Text(ref.c_str());
            }
            ImGui::EndListBox();
        }
    }

    void GuiButtons()
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
            if (ImGui::Button("Open General Layer"))
            {
                m_Layers[0] = true;
                m_LayerRefs[0] = MPE::NEWREF<GeneralTestLayer>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[0]);
            }

            if (ImGui::Button("Open Textures Layer"))
            {
                m_Layers[1] = true;
                m_LayerRefs[1] = MPE::NEWREF<TexturesTestLayer>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[1]);
            }
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
        MPE_CORE_INFO("General Layer: {0}", m_Layers[0] ? "true" : "false");
        MPE_CORE_INFO("Textures Layer: {0}", m_Layers[1] ? "true" : "false");
    }

    std::array<bool, 2> m_Layers = {false};
    MPE::REF<MPE::Layer> m_LayerRefs[2];
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
        PushOverlay(MPE::NEWREF<ProjectPickerGuiLayer>());
    }

    ~ProjectPicker() {}
};

MPE::App* MPE::CreateApp()
{
    return new ProjectPicker();
}