#include <iostream>
#include <Test/Test.h>
#include <MPE.h>
#include <EntryPoint.h>

void timer_test();
void processHeavyTask();
void anotherTask();
void log_test(MPE::Log &log);

class DummyApp : public MPE::App
{
public:
    DummyApp()
    {
        MPE_CORE_TRACE("DummyApp created!");
    }

    ~DummyApp()
    {
        MPE_CORE_TRACE("DummyApp destroyed!");
    }

    void Run() override
    {
        MPE_CORE_TRACE("DummyApp running!");
        MPE::Test test;
        MPE_CORE_INFO("Test: {0}", test.GetName());

        MPE_PROFILE_START("MainSession", "main_profile.json");

        processHeavyTask();
        anotherTask();

        timer_test();

        MPE_PROFILE_END();

        MPE::Log log("Main", MPE::Log::Option::CONSOLE | MPE::Log::Option::FILE, "main");
        log.info("Hello, Custom Sink Log!");
        log.trace("Hello, Custom Sink Log!");
        log_test(log);
    }
};

MPE::REF<MPE::App> MPE::CreateApp()
{
    return NEWREF<DummyApp>();
}

void log_test(MPE::Log &log)
{
    log.info("Hello, Custom Sink Log!");
    log.trace("Hello, Custom Sink Log!");
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