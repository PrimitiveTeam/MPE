#pragma once

#include <string>

namespace MPE
{
    class Test
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