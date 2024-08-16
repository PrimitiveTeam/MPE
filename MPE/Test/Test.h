#pragma once

#include "MPE/Core/_CORE.h"

#include <string>

namespace MPE
{
class MPE_API Test
{
  public:
    Test();
    ~Test();

    std::string GetName() const { return m_name; }
    void SetName(const std::string &name) { m_name = name; }

  private:
    std::string m_name;
};
}