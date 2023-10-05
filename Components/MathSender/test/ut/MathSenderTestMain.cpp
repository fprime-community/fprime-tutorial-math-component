// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "MathSenderTester.hpp"
#include "STest/Random/Random.hpp"

/*
TEST(Nominal, ToDo) {
    MathModule::MathSenderTester tester;
    tester.toDo();
}
*/

TEST(Nominal, AddCommand) {
    MathModule::MathSenderTester tester;
    tester.testAddCommand();
}

TEST(Nominal, Result) {
    MathModule::MathSenderTester tester; ///@TODO
    tester.testResult();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
