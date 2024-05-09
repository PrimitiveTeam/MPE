#include <gtest/gtest.h>

#include <MPE.h>

namespace MPE_TEST
{
    class Time_Test : public ::testing::Test
    {
    protected:
        MPE::Time *time;

        void SetUp() override
        {
            time = new MPE::Time(0.0f);
        }

        void TearDown() override
        {
            delete time;
        }
    };

    TEST_F(Time_Test, CoreDeltaTimeTest)
    {
        EXPECT_EQ(time->GetSeconds(), 0.0f);
        EXPECT_EQ(time->GetMilliSeconds(), 0.0f);
    }

}

int main(int argc, char **argv)
{
    // Init can only be called once per source file
    MPE::GlobalLog::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}