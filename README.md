# MathComponent Tutorial 

Welcome to the MathComponent tutorial!

This tutorial shows how to develop, test, and deploy a simple topology
consisting of two components:

1. `MathSender`: A component that receives commands and forwards work to
   `MathReceiver`.

2. `MathReceiver`: A component that carries out arithmetic operations and
   returns the results to `MathSender`.

See the diagram below.

<a name="math-top"></a>
![A simple topology for arithmetic computation](docs/img/top.png)

## What is covered
This tutorial will cover the following concepts:

1. Defining types, ports, and components in F'. 

2. Creating a deployment and running F' GDS. 

3. Writing unit tests.

4. Handling errors, creating events, and adding telemetry channels. 

## Prequisites 
This tutorial assumes the following:

1. Basic knowledge of Unix: How to navigate in a shell and execute programs.

2. Basic knowledge of C++.

3. We advise new F' users to try the [Hello World Tutorial](https://fprime-community.github.io/fprime-tutorial-hello-world/)


**Next:** [Start the MathComponent Tutorial: Defining Types](./docs/defining-types.md)