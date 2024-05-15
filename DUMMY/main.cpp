#include <EntryPoint.h>
#include <MPE.h>
#include <Test/Test.h>
#include <iostream>

void timer_test();
void processHeavyTask();
void anotherTask();
void log_test(MPE::Log &log);

class DummyApp : public MPE::App
{
  public:
    DummyApp() { MPE_CORE_TRACE("DummyApp created!"); }

    ~DummyApp() { MPE_CORE_TRACE("DummyApp destroyed!"); }

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

        // Random event test
        MPE::FunctionCalledEvent funcEvent("SampleFunction");
        OnEvent(funcEvent);

        // Try catch custom Error
        try
        {
            throw MPE::Error(404, "Not Found", MPE::Severity::Error, MPE::Category::Global);
        }
        catch (const MPE::Error &e)
        {
            e.std_log();
        }

        // Try catch from pre-defined exceptions
        try
        {
            throw MPE_ERROR_1001;
        }
        catch (const std::exception &e)
        {
            MPE_CORE_ERROR("Exception: {0}", e.what());
        }

        // Try catch from pre-defined exceptions
        try
        {
            // throw MPE::ErrorRegistry::get(1001);
            throw MPE_ERROR_1001;
        }
        catch (const MPE::Error &e)
        {
            MPE_CORE_ERROR("Exception: {0}", e.get_verbose_log());
        }

        // Show a message box
        try
        {
            // throw MPE::ErrorRegistry::get(1001);
            throw MPE_ERROR_1001;
        }
        catch (const MPE::Error &e)
        {
            MPE_CORE_ERROR("Exception: {0}", e.get_verbose_log());
            e.showExceptionDialog(e);
            MPE::Error::showExceptionDialog(e);
        }
    }

  private:
    bool TestFunc(MPE::FunctionCalledEvent &event)
    {
        MPE_CORE_TRACE("TestFunc called!");
        return true;
    }
    // Used when another function is called
    void OnEvent(MPE::Event &e)
    {
        MPE::EventDispatcher dispatcher(e);
        // dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(DummyApp::TestFunc));
        dispatcher.Dispatch<MPE::FunctionCalledEvent>(MPE_BIND_EVENT_FUNCTION(DummyApp::TestFunc));
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
#ifdef MPE_COMPILER_APPLECLANG
        value = value + i;
#else
        value += i;
#endif
    }
}

void anotherTask()
{
    MPE_PROFILE_FUNCTION();

    // Another simulated task
    volatile int sum = 1;
    for (int i = 1; i < 1000; ++i)
    {
#ifdef MPE_COMPILER_APPLECLANG
        sum = sum * i;
#else
        sum *= i;
#endif
    }
}