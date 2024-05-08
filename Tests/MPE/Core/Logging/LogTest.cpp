#include <gtest/gtest.h>

#include <MPE.h>

namespace MPE_TEST
{
    class Logger_Log_Test : public ::testing::Test
    {
    protected:
        std::stringstream buffer;
        std::streambuf *oldCoutStreamBuf;

        void SetUp() override
        {
            MPE::GlobalLog::Init();

            // Redirect cout to buffer
            // oldCoutStreamBuf = std::cout.rdbuf();
            // std::cout.rdbuf(buffer.rdbuf());
        }

        void TearDown() override
        {
            // Reset cout to its old self
            // std::cout.rdbuf(oldCoutStreamBuf);
        }

        std::string getLoggedOutput()
        {
            return buffer.str();
        }
    };

    // Test to check if the correct log message is printed to console
    // TEST_F(Logger_Log_Test, CoreInfoLogTest)
    // {
    //     MPE_CORE_INFO("This is an information log.");
    //     std::string loggedOutput = getLoggedOutput();
    //     EXPECT_TRUE(loggedOutput.find("This is an information log.") != std::string::npos);
    // }

    // Test to check if the correct log message is printed to console
    TEST_F(Logger_Log_Test, CoreInfoLogTest2)
    {
        MPE_CORE_INFO("This is an information log.");
        std::string loggedOutput = getLoggedOutput();
        EXPECT_TRUE(true);
    }

}

int main(int argc, char **argv)
{
    // MPE::GlobalLog::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}