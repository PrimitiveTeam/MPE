#include <gtest/gtest.h>

#include <MPE.h>

namespace MPE_TEST
{
    class Logger_Log_Test : public ::testing::Test
    {
    protected:
        MPE::Log *logger;

        void SetUp() override
        {
            logger = new MPE::Log("TestLogger", MPE::Log::MEMORY);
        }

        void TearDown() override
        {
            delete logger;
        }
    };

    // Test to check if the correct log message is printed to console
    TEST_F(Logger_Log_Test, CoreInfoLogTest)
    {
        logger->info("This is an information log.");
        std::string loggedOutput = logger->getOutput();
        EXPECT_TRUE(loggedOutput.find("This is an information log.") != std::string::npos);
        MPE_CORE_INFO("Sink: {0}", loggedOutput);
    }

}

int main(int argc, char **argv)
{
    // Init can only be called once per source file
    MPE::GlobalLog::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}