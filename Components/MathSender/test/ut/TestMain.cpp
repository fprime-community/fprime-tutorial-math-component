// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include "STest/Random/Random.hpp"

/*
TEST(Nominal, ToDo) {
    MathModule::Tester tester;
    tester.toDo();
}
*/

TEST(Nominal, AddCommand) {
    MathModule::Tester tester;
    tester.testAddCommand();
}

TEST(Nominal, Result) {
    MathModule::Tester tester; ///@TODO
    tester.testResult();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
    STest::Random::seed();
}
