#include "LayerStack.h"
#include "MPE/MPEPCH.h"

namespace MPE
{
LayerStack::LayerStack() {}

LayerStack::~LayerStack()
{
    for (REF<Layer> layer : SYS_Layers)
    {
        layer.reset();
    }
}

void LayerStack::PushLayer(const REF<Layer> &layer)
{
    SYS_Layers.emplace(SYS_Layers.begin() + SYS_LayerInsertIndex, layer);
    SYS_LayerInsertIndex++;
}

void LayerStack::PopLayer()
{
    if (SYS_LayerInsertIndex > 0)
    {
        auto it = SYS_Layers.begin() + (SYS_LayerInsertIndex - 1);
        (*it)->OnDetach();
        SYS_Layers.erase(it);
        SYS_LayerInsertIndex--;
    }
}

void LayerStack::PushOverlay(const REF<Layer> &overlay)
{
    SYS_Layers.emplace_back(overlay);
}

void LayerStack::PopOverlay()
{
    if (!SYS_Layers.empty() && SYS_LayerInsertIndex < SYS_Layers.size())
    {
        auto it = SYS_Layers.end() - 1;
        (*it)->OnDetach();
        SYS_Layers.pop_back();
    }
}
}