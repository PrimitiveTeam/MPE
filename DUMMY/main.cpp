#include <iostream>
#include <Test/Test.h>
#include <MPE.h>

void timer_test();
void processHeavyTask();
void anotherTask();

int main()
{
    MPE::Log::Init();
    SET_EXECUTABLE_PATH_AS_CWD();
    MPE_CORE_TRACE("Hello, MPE!");

    MPE::Test test;
    MPE_CORE_INFO("Test: {0}", test.GetName());

    MPE_PROFILE_START("MainSession", "main_profile.json");

    processHeavyTask();
    anotherTask();

    timer_test();

    MPE_PROFILE_END();

    return 0;
}

void timer_test()
{
    MPE::_TIMER timer("Function Profile", true);

    // Pause the main thread for 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void processHeavyTask()
{
    MPE_PROFILE_FUNCTION();

    // Simulate some heavy processing
    volatile int value = 0;
    for (int i = 0; i < 1000000; ++i)
    {
        value += i;
    }
}

void anotherTask()
{
    MPE_PROFILE_FUNCTION();

    // Another simulated task
    volatile int sum = 1;
    for (int i = 1; i < 1000; ++i)
    {
        sum *= i;
    }
}