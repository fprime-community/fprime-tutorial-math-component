# Writing Unit Tests Part 1: Creating the Implementation Stub

## Background 

**Unit tests** are an important part of FSW development. At the component level, unit tests typically invoke input ports, send commands, and check for expected values on output ports (including telemetry and event ports).


## In this Section 

In this section of the tutorial, you will create a stub implementation of a unit test that will test `MathSender`. 

First, let's create our Unit Test build cache:

```shell
# In MathProject
fprime-util generate --ut 
```

In Components/MathSender, create a directory called test/ut

```shell 
# In: MathSender
mkdir -p test/ut
```

Add the unit test to the build. Absolutely make sure that this is BELOW the existing stuff in the CMakeLists.txt:

```cmake 
# In: MathSender/CMakeLists.txt
# Below: register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/MathSender.fpp"
)
set(UT_AUTO_HELPERS ON)
register_fprime_ut()
```

## Generate the Unit Test Stub 
Generate a stub implementation of the unit tests.
This stub contains all the boilerplate necessary to write and run unit tests against the `MathSender` component:

```shell 
# In: MathSender
fprime-util impl --ut
```

You have just generate three new files ```MathSenderTester.cpp MathSenderTester.hpp MathSenderTestMain.cpp```. Move these files to the `test/ut` in MathSender using:

```shell 
# In: MathSender
mv MathSenderTester.* MathSenderTestMain.cpp test/ut
```

## Add the Tests to the Build

Add `MathSenderTester.cpp` and `MathSenderTestMain.cpp` to the build. Do so by editing the CMakeLists.txt to add the 2 new source files. The UT section should now look like the following:

```cmake
# In: MathSender/CMakeLists.txt 
set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/MathSender.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/MathSenderTester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/MathSenderTestMain.cpp"
)
set(UT_AUTO_HELPERS ON)
register_fprime_ut()
```

> Note: most of this is from a few steps ago, you will only be adding two lines in this step. 

Build the unit test in MathSender:

```shell 
# In: MathSender
fprime-util build --ut 
```
> Don't forget to add ```--ut``` or else you are just going to build the component again. 

## (Optional) Inspect the generated code
The unit test build generates some code to support unit testing. The code is located at `MathSender/build-fprime-automatic-native-ut/Components/MathSender`.
This directory contains two auto-generated classes:

1. `MathSenderGTestBase`: This is the direct base class of `Tester`. It provides a test interface implemented with Google Test macros.

2. `MathSenderTesterBase`: This is the direct base class of `MathSenderGTestBase`.
It provides basic features such as histories of port invocations. It is not specific to Google Test, so you can use this class without Google Test if desired.

You can look at the header files for these generated classes to see what operations they provide.
In the next sections we will provide some example uses of these operations.


## Summary

In this section you created the stub implementation of a unit test. In the next section you will finish the unit test and run it. 

**Next:** [Writing Unit Tests Part 2: Completing the Stub & Running the Test](./writing-unit-tests-2.md)


