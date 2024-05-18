#include <EntryPoint.h>
#include <MPE.h>
#include <Test/Test.h>
#include <iostream>

void timer_test();
void processHeavyTask();
void anotherTask();
void log_test(MPE::Log &log);

class DummyLayer : public MPE::Layer
{
  public:
    DummyLayer() : Layer("DummyLayer")
    {
        MPE_CORE_TRACE("DummyLayer created!");

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
            // e.showExceptionDialog(e);
            // MPE::Error::showExceptionDialog(e);
        }
    }

    ~DummyLayer() { MPE_CORE_TRACE("DummyLayer destroyed!"); }

    void OnAttach() override { MPE_CORE_TRACE("DummyLayer attached!"); }

    void OnDetach() override { MPE_CORE_TRACE("DummyLayer detached!"); }

    void OnUpdate(MPE::Time deltatime) override { MPE_CORE_TRACE("DummyLayer updated! DeltaTime: {0}", deltatime.GetMilliSeconds()); }

    void OnImGuiRender() override { MPE_CORE_TRACE("DummyLayer ImGui rendered!"); }

    void OnEvent(MPE::Event &event) override
    {
        MPE::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(DummyLayer::OnKeyPressed));
        dispatcher.Dispatch<MPE::FunctionCalledEvent>(MPE_BIND_EVENT_FUNCTION(DummyLayer::TestFunc));
    }

    bool OnKeyPressed(MPE::KeyPressedEvent &event)
    {
        MPE_CORE_TRACE("Key pressed: {0}", event.GetKeyCode());
        return true;
    }

  private:
    bool TestFunc(MPE::FunctionCalledEvent &event)
    {
        MPE_CORE_TRACE("TestFunc called!");
        return true;
    }
};

class TestLayer : public MPE::Layer
{
  public:
    TestLayer() : Layer("TestLayer") { MPE_CORE_TRACE("TestLayer created!"); }

    ~TestLayer() { MPE_CORE_TRACE("TestLayer destroyed!"); }

    void OnAttach() override { MPE_CORE_TRACE("TestLayer attached!"); }

    void OnDetach() override { MPE_CORE_TRACE("TestLayer detached!"); }

    void OnUpdate(MPE::Time deltatime) override { MPE_CORE_TRACE("TestLayer updated! DeltaTime: {0}", deltatime.GetMilliSeconds()); }

    void OnImGuiRender() override { MPE_CORE_TRACE("TestLayer ImGui rendered!"); }

    void OnEvent(MPE::Event &event) override
    {
        MPE::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(TestLayer::OnKeyPressed));
    }

    bool OnKeyPressed(MPE::KeyPressedEvent &event)
    {
        MPE_CORE_TRACE("Key pressed: {0}", event.GetKeyCode());
        return true;
    }
};

class DummyApp : public MPE::App
{
  public:
    DummyApp()
    {
        MPE_CORE_TRACE("DummyApp created!");
        PushLayer(MPE::NEWREF<DummyLayer>());
        PushLayer(MPE::NEWREF<TestLayer>());
    }

    ~DummyApp()
    {
        // Pop all layers
        PopAllLayers();
        MPE_CORE_TRACE("DummyApp destroyed!");
    }
};

MPE::App *MPE::CreateApp()
{
    return new DummyApp();
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