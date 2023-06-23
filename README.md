# Math Component Tutorial 

Welcome to the newest Math Component tutorial!

This tutorial shows how to develop, test, and deploy a simple topology
consisting of two components:

1. `MathSender`: A component that receives commands and forwards work to
   `MathReceiver`.

1. `MathReceiver`: A component that carries out arithmetic operations and
   returns the results to `MathSender`.

See the diagram below.

<a name="math-top"></a>
![A simple topology for arithmetic computation](png/top.png)

**What is covered:** The tutorial covers the following concepts:

1. Using the [FPP modeling language](https://fprime-community.github.io/fpp) to
   specify the types and ports used by the components.

1. Using the F Prime build system to build the types and ports.

1. Developing the `MathSender` component: Specifying the component, building
   the component, completing the C++ component implementation, and writing
   component unit tests.

1. Developing the `MathReceiver` component.

1. Adding the new components and connections to the F Prime `Ref` application.

1. Using the F Prime Ground Data System (GDS) to run the updated `Ref`
   application.

**Prerequisites:** This tutorial assumes the following:

1. Basic knowledge of Unix: How to navigate in a shell and execute programs.

1. Basic knowledge of git: How to create a branch.

1. Basic knowledge of C++, including class declarations, inheritance,
and virtual functions.