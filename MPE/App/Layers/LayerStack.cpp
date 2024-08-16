#include "LayerStack.h"
#include "MPE/MPEPCH.h"

namespace MPE
{
LayerStack::LayerStack() {}

LayerStack::~LayerStack()
{
    for (REF<Layer> layer : m_layers)
    {
        layer.reset();
    }
}

void LayerStack::PushLayer(const REF<Layer> &layer)
{
    m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
    m_layerInsertIndex++;
}

void LayerStack::PopLayer()
{
    if (m_layerInsertIndex > 0)
    {
        auto it = m_layers.begin() + (m_layerInsertIndex - 1);
        (*it)->OnDetach();
        m_layers.erase(it);
        m_layerInsertIndex--;
    }
}

void LayerStack::PopLayer(const REF<Layer> &layer)
{
    auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIndex, layer);
    if (it != m_layers.begin() + m_layerInsertIndex)
    {
        (*it)->OnDetach();
        m_layers.erase(it);
        m_layerInsertIndex--;
    }
}

void LayerStack::PushOverlay(const REF<Layer> &overlay)
{
    m_layers.emplace_back(overlay);
}

void LayerStack::PopOverlay()
{
    if (!m_layers.empty() && m_layerInsertIndex < m_layers.size())
    {
        auto it = m_layers.end() - 1;
        (*it)->OnDetach();
        m_layers.pop_back();
    }
}

void LayerStack::PopOverlay(const REF<Layer> &overlay)
{
    auto it = std::find(m_layers.begin() + m_layerInsertIndex, m_layers.end(), overlay);
    if (it != m_layers.end())
    {
        (*it)->OnDetach();
        m_layers.erase(it);
    }
}
}