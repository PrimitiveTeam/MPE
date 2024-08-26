#include "PropertyViewerTest.h"
#include "MPE/MPEPCH.h"

#include "MPE/Vendor/GLM/GLM.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

PropertyViewerTest::PropertyViewerTest() : Layer("Editor")
{
    m_sceneManager = MPE::NEWSCOPE<MPE::SceneManager>();
    m_scene = MPE::NEWREF<MPE::Scene>();
    m_sceneManager->PushScene(m_scene);

    m_objectHierarchy = MPE::NEWREF<MPE::ObjectHierarchy>(*m_scene->GetObjects());
    m_propertyViewer = MPE::NEWREF<MPE::PropertyViewer>(*m_scene->GetECS());

    // auto &object = m_scene->CreateObject<MPE::Cube>();
}

void PropertyViewerTest::OnUpdate(MPE::Time deltaTime)
{
    // MPE::RenderPrimitive::SetClearColor(glm::vec4(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    // MPE::RenderPrimitive::Clear();
    m_sceneManager->OnUpdate(deltaTime);
    m_sceneManager->OnRender();
    m_objectHierarchy->OnUpdate(deltaTime);
}

void PropertyViewerTest::OnImGuiRender()
{
    m_sceneManager->OnImGuiRender();

    ImGui::Begin("Object Hierarchy Manipulation");

    if (m_objectHierarchy->GetSelectedEntity() != entt::null)
    {
        ImGui::Text("Selected Entity: %d", m_objectHierarchy->GetSelectedEntity());
        m_propertyViewer->SetEntity(m_objectHierarchy->GetSelectedEntity());
    }
    else
    {
        m_propertyViewer->UnsetEntity();
    }

    m_propertyViewer->OnImGuiRender();

    if (m_propertyViewer->EntityModified())
    {
        m_objectHierarchy->UpdateHierarchyList();
    }

    if (ImGui::Button("Add Object"))
    {
        AddObject();
    }

    ImGui::SameLine();

    if (ImGui::Button("Remove Object"))
    {
        RemoveObject();
    }

    m_objectHierarchy->OnImGuiRender();

    ImGui::End();
}

void PropertyViewerTest::OnEvent(MPE::Event &event)
{
    m_sceneManager->OnEvent(event);
    m_objectHierarchy->OnEvent(event);
    // MPE::EventDispatcher dispatcher(event);
    // dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(PropertyViewerTest::OnKeyPressedEvent));
}

bool PropertyViewerTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void PropertyViewerTest::AddObject()
{
    auto &object = m_scene->CreateObject<MPE::Cube>();
    m_objectHierarchy->UpdateHierarchyList();
}

void PropertyViewerTest::RemoveObject()
{
    auto objects = m_scene->GetObjects();

    if (objects->empty())
    {
        return;
    }

    objects->pop_back();
    m_objectHierarchy->UpdateHierarchyList();
}