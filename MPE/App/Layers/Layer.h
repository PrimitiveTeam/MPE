#pragma once

#include "MPE/Events/Event.h"
#include "MPE/Time/Time.h"

#include <string>
#include <memory>

namespace MPE
{
class MPE_API Layer : public std::enable_shared_from_this<Layer>
{
  protected:
    std::string m_layerName;

  public:
    Layer(const std::string &layerName = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate(Time deltaTime) {}
    virtual void OnImGuiRender() {}
    virtual void OnEvent(Event &event) {}

    inline const std::string &GetName() const { return m_layerName; }
};
}