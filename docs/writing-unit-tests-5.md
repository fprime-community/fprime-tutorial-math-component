# Writing Unit Tests Part 5: Creating the Implementation Stub

## In this Section 

In this section of the tutorial, you will be repeating the steps you used to create an implementation stub for `MathSender`. 

## Create a Directory for the Unit Tests 
In `Components/MathReceiver`, create a directory called test/ut 

```shell 
# In: MathReceiver
mkdir -p test/ut
```

Add the unit test to the build. Absolutely make sure that this is BELOW the existing stuff in the CMakeLists.txt:

```cmake 
# In: MathReceiver/CMakeLists.txt
# Below: register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/MathReceiver.fpp"
)
set(UT_AUTO_HELPERS ON)
register_fprime_ut()
```

## Generate the unit test stub 
Generate a stub implementation of the unit tests.

```shell 
# In: MathReceiver
fprime-util impl --ut
```
> These commands may take a while to run.

You haved just generate three new files `Tester.cpp Tester.hpp TestMain.cpp`. Move these files to the test/ut directory in MathReceiver using:

```shell 
# In: MathReceiver
mv Tester.* TestMain.cpp test/ut
```

Add `Tester.cpp and TestMain.cpp` to the build. Do so by editing the CMakeLists.txt in MathReceiver: 

```cmake
# In: MathReceiver/CMakeLists.txt 
set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/MathReceiver.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestMain.cpp"
)
set(UT_AUTO_HELPERS ON)
register_fprime_ut()
```

> Note: most of this is from a few steps ago, you will only be adding two lines in this step. 

Build the unit test in MathReceiver:

```shell 
# In: MathReceiver
fprime-util build --ut 
```
> Don't forget to add ```--ut``` or else you are just going to build the component again. 


## Preparing for Random Testing

Complete the following steps to prepare for random testing. 


```cpp
// In: Tester.cpp
#include "Tester.hpp"
#include "STest/Pick/Pick.hpp"
```

```cpp
// In: TestMain.cpp
#include "Tester.hpp"
#include "STest/Random/Random.hpp"
```

```cpp
// In: TestMain.cpp
// Within: int main(){
STest::Random::seed();
```

```cmake 
# In: /MathReceiver/CMakeLists.txt
# Above: register_fprime_ut()
set(UT_MOD_DEPS STest)
```

## Summary 

In this section you have setup implementation stubs to begin writing unit tests for `MathReceiver`. 

**Next:** [Writing Unit Tests 6](./writing-unit-tests-6.md)
