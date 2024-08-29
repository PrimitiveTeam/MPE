#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Input/Input.h"

namespace MPE
{
class MPE_API RPIInput : public Input
{
  protected:
    virtual bool IsKeyPressedImpl(int keycode) override;
    virtual bool IsMouseButtonPressedImpl(int button) override;
    virtual std::pair<float, float> GetMousePositionImpl() override;
    virtual float GetMouseXImpl() override;
    virtual float GetMouseYImpl() override;
};
}