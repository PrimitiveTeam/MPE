#pragma once

#include "MPE/Core/_CORE.h"

#include <string>

namespace MPE
{
class MPE_API Test
{
  private:
    std::string m_Name;

  public:
    Test();
    ~Test();

    std::string GetName() const { return m_Name; }
    void SetName(const std::string &name) { m_Name = name; }
};
}