#include "ObjectHierarchyTest.h"
#include "MPE/MPEPCH.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#ifdef MPE_OPENGL
#    include "MPE/MPEGFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPEGFX_OPEN_GL_ES.h"
#endif

ObjectHierarchyTest::ObjectHierarchyTest() : Layer("Editor")
{
    m_sceneManager = MPE::NEWSCOPE<MPE::SceneManager>();
    m_scene = MPE::NEWREF<MPE::Scene>();
    m_sceneManager->PushScene(m_scene);

    m_objectHierarchy = MPE::NEWREF<MPE::ObjectHierarchy>(*m_scene->GetObjects());

    // auto &object = m_scene->CreateObject<MPE::Cube>();
}

void ObjectHierarchyTest::OnUpdate(MPE::Time deltaTime)
{
    // MPE::RenderPrimitive::SetClearColor(glm::vec4(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    // MPE::RenderPrimitive::Clear();
    m_sceneManager->OnUpdate(deltaTime);
    m_sceneManager->OnRender();
    m_objectHierarchy->OnUpdate(deltaTime);
}

void ObjectHierarchyTest::OnImGuiRender()
{
    m_sceneManager->OnImGuiRender();

    ImGui::Begin("Object Hierarchy");

    if (ImGui::Button("Add Object"))
    {
        AddObject();
    }

    ImGui::SameLine();

    if (ImGui::Button("Remove Object"))
    {
        RemoveObject();
    }

    ImGui::Text("Object Hierarchy");
    ImGui::Text("Object List:");
    ImGui::Text("%s", m_objectHierarchy->GetObjectList().c_str());

    ImGui::End();
}

void ObjectHierarchyTest::OnEvent(MPE::Event &event)
{
    m_sceneManager->OnEvent(event);
    m_objectHierarchy->OnEvent(event);
    // MPE::EventDispatcher dispatcher(event);
    // dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(ObjectHierarchyTest::OnKeyPressedEvent));
}

bool ObjectHierarchyTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void ObjectHierarchyTest::AddObject()
{
    auto &object = m_scene->CreateObject<MPE::Cube>();
    m_objectHierarchy->UpdateHierarchyList();
}

void ObjectHierarchyTest::RemoveObject()
{
    auto objects = m_scene->GetObjects();

    if (objects->empty())
    {
        return;
    }

    objects->pop_back();
    m_objectHierarchy->UpdateHierarchyList();
}