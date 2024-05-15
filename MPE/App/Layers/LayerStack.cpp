#include "LayerStack.h"
#include "MPE/MPEPCH.h"

namespace MPE
{
LayerStack::LayerStack() {}

LayerStack::~LayerStack()
{
    for (Layer *layer : SYS_Layers)
    {
        delete layer;
    }
}

void LayerStack::PushLayer(Layer *layer)
{
    SYS_Layers.emplace(SYS_Layers.begin() + SYS_LayerInsertIndex, layer);
    SYS_LayerInsertIndex++;
}

void LayerStack::PushOverlay(Layer *overlay)
{
    SYS_Layers.emplace_back(overlay);
}

void LayerStack::PopLayer(Layer *layer)
{
    auto it = std::find(SYS_Layers.begin(), SYS_Layers.end(), layer);
    if (it != SYS_Layers.end())
    {
        SYS_Layers.erase(it);
        SYS_LayerInsertIndex--;
    }
}

void LayerStack::PopOverlay(Layer *overlay)
{
    auto it = std::find(SYS_Layers.begin(), SYS_Layers.end(), overlay);
    if (it != SYS_Layers.end())
    {
        SYS_Layers.erase(it);
    }
}
}