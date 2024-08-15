#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/App/Layers/Layer.h"

#include <vector>

namespace MPE
{
class MPE_API LayerStack
{
  private:
    std::vector<REF<Layer>> m_layers;
    unsigned int m_layerInsertIndex = 0;

  public:
    LayerStack();
    ~LayerStack();

    void PushLayer(const REF<Layer> &layer);
    void PopLayer();
    void PopLayer(const REF<Layer> &layer);

    void PushOverlay(const REF<Layer> &overlay);
    void PopOverlay();
    void PopOverlay(const REF<Layer> &overlay);

    bool empty() { return m_layers.empty(); }
    size_t size() { return m_layers.size(); }

    std::vector<REF<Layer>>::iterator begin() { return m_layers.begin(); }
    std::vector<REF<Layer>>::iterator end() { return m_layers.end(); }

    const std::vector<REF<Layer>> &GetLayers() const { return m_layers; }
};
}