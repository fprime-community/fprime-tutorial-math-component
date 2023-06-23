# Constructing Ports 

## Background 

A **port** is the endpoint of a connection between
two components.
A **port definition** is like a function signature;
it defines the type of the data carried on a port.

## Requirements
For this tutorial, you will need two port definitions:

* `OpReqest` for sending an arithmetic operation request from
`MathSender` to `MathReceiver`.

* `MathResult` for sending the result of an arithmetic
operation from `MathReceiver` to `MathSender`.

## In this section 

In this section, you will create a `Ports` directory where you will create two ports in `MathPorts.fpp`. You will add the ports directory into the project build and built `Ports`. 

## Setup 

Start by making a directory where the ports will be defined. Create a directory called `Ports` in the `MathProject` directory:

```shell 
# In: MathProject
mkdir -p Ports 
cd Ports
```

While in "Ports", create an empty fpp file called `MathPorts.fpp`, this is where the ports will be defined:

```shell 
# In: Ports
touch MathPorts.fpp
```

## Implementing the Ports

Use your favorite text editor to add the following to `MathPorts.fpp`: 

```fpp
# In: MathPorts.fpp
module MathModule{ 
  @ Port for requesting an operation on two numbers
  port OpRequest(
    val1: F32 @< The first operand
    op: MathOp @< The operation
    val2: F32 @< The second operand
  )

  @ Port for returning the result of a math operation
  port MathResult(
    result: F32 @< the result of the operation
  )
}
```
> Notice how MathModule appears again while defining the ports. 

Here, you have created two ports. The first port, called OpRequest, carries two 32-bit floats (`val1` and `val2`) and a math operations `op`. The second port only carries one 32-bit float (result). The first port is intended to send an opperation and opperands to the `MathReceiver`. The second port is designed to send the results of the operation back to `MathSender`. 

## Adding to the Build 

Create a `CMakeLists.txt` file in `Ports`. 

```shell 
# In: Ports
touch CMakeLists.txt
```

Add the following to the `CMakeLists.txt`. 

```cmake
# In: Ports/CMakeLists.txt
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/MathPorts.fpp"
)

register_fprime_module()
```

 Add the following to `project.cmake`. Remember that `project.cmake` is in MathProject, not Ports. 

```cmake 
# In: MathProject/project.cmake
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Ports/")
```

Ports should build without any issues. Use the following build.

```shell
# In: Ports
fprime-util generate
fprime-util build
```

`MathProject/build-fprime-automatic-native/Ref/MathPorts`.
For port definitions, the names of the auto-generated C++
files end in `PortAc.hpp` and `PortAc.cpp`.
Note however, the auto-generated C++ port files are used
by the autocoded component implementations;
you won't ever program directly against their interfaces.

## Conclusion
At this point, you have succefully implemented all the ports 
used for this tutorial and added them to the build. 


**Next:** [Creating Components 1](./creating-components-1.md)