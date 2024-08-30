#include "EditorSource.h"

EditorCoreLayer::EditorCoreLayer() : Layer("EditorCoreLayer") {}

void EditorCoreLayer::OnAttach() {}

void EditorCoreLayer::OnDetach() {}

void EditorCoreLayer::OnUpdate(MPE::Time deltaTime) {}

void EditorCoreLayer::OnImGuiRender()
{
    ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoSavedSettings);

    ImGui::End();
}

void EditorCoreLayer::OnEvent(MPE::Event& event) {}