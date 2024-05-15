#pragma once

#include "MPE/App/Layers/Layer.h"

#include <vector>

namespace MPE
{
class MPE_API LayerStack
{
  private:
    std::vector<Layer *> SYS_Layers;
    unsigned int SYS_LayerInsertIndex = 0;

  public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);
    void PopLayer(Layer *layer);
    void PopOverlay(Layer *overlay);

    std::vector<Layer *>::iterator begin() { return SYS_Layers.begin(); }
    std::vector<Layer *>::iterator end() { return SYS_Layers.end(); }
};
}