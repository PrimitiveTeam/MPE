#include <iostream>
#include <Test/Test.h>
#include <MPE.h>

int main()
{
    MPE::Log::Init();
    MPE_CORE_TRACE("Hello, MPE!");

    MPE::Test test;
    MPE_CORE_INFO("Test: {0}", test.GetName());

    return 0;
}