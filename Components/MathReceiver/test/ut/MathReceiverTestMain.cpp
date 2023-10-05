// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "MathReceiverTester.hpp"
#include "STest/Random/Random.hpp"

/*
TEST(Nominal, ToDo) {
    MathModule::MathReceiverTester tester;
    tester.toDo();
}
*/

TEST(Nominal, AddCommand) {
    MathModule::MathReceiverTester tester;
    tester.testAdd();
}

TEST(Nominal, SubCommand) {
    MathModule::MathReceiverTester tester;
    tester.testSub();
}

TEST(Nominal, Throttle) {
    MathModule::MathReceiverTester tester;
    tester.testThrottle();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
