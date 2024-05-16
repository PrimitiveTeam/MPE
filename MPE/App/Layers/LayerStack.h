#pragma once

#include "MPE/App/Layers/Layer.h"

#include <vector>

namespace MPE
{
class MPE_API LayerStack
{
  private:
    std::vector<REF<Layer>> SYS_Layers;
    unsigned int SYS_LayerInsertIndex = 0;

  public:
    LayerStack();
    ~LayerStack();

    void PushLayer(const REF<Layer> &layer);
    void PopLayer();
    void PushOverlay(const REF<Layer> &overlay);
    void PopOverlay();

    bool empty() { return SYS_Layers.empty(); }

    std::vector<REF<Layer>>::iterator begin() { return SYS_Layers.begin(); }
    std::vector<REF<Layer>>::iterator end() { return SYS_Layers.end(); }
};
}