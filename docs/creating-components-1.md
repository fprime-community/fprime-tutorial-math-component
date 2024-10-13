# Creating Components Part 1: Creating the MathSender

## Background 

Components are the lifeblood of an F' deployment. In this tutorial the components are strictly virtual, however in many deployments components will represent unique pieces of hardware, such as sensors and microcontrollers! 

## In this section 

In this section, you will begin creating an active component and write its F Prime Prime (fpp) implementation. You will generate cpp and hpp files using the fpp. Note, that you will implement component behavior in `MathSender.cpp` in the next section. Most commonly, the steps to create a new component are the following:
1. Construct the FPP model.
2. Add the model to the project.
3. Build the stub implementation.
4. Complete the implementation.
5. Write and run unit tests.


## Component Description 
The `MathSender` is an active component which receives parameters, sends parameters, logs events, and sends telemetry. 

With the component description in mind, use the following command to create the `MathSender` component:

## Creating the MathSender
F´ projects conveniently come with a `Components/` folder to create components in. It is not required for components to live there, but this tutorial will make use of it.

```shell
# In: MathProject/Components/
fprime-util new --component 
```
This command will prompt you for some inputs. Answer the prompts as shown below: 

```
[INFO] Cookiecutter source: using builtin
Component name [MyComponent]: MathSender 
Component short description [Example Component for F Prime FSW framework.]: Active component used for sending operations and operands to the MathReceiver.
Component namespace [Component]: MathModule
Select component kind:
1 - active
2 - passive
3 - queued
Choose from 1, 2, 3 [1]: 1
Enable Commands?:
1 - yes
2 - no
Choose from 1, 2 [1]: 1
Enable Telemetry?:
1 - yes
2 - no
Choose from 1, 2 [1]: 1
Enable Events?:
1 - yes
2 - no
Choose from 1, 2 [1]: 1
Enable Parameters?:
1 - yes
2 - no
Choose from 1, 2 [1]: 1
[INFO] Found CMake file at 'MathProject/project.cmake'
Add component Components/MathSender to MathProject/project.cmake at end of file (yes/no)? yes
Generate implementation files (yes/no)? yes
```


Before doing anything to the files you have just generated, try building:

```shell 
cd MathSender
fprime-util build
```

## Editing the FPP Model 
Now that you have created the component, you can start working on implementing the component behavior. The first part of implementing component behavior is editing the fpp file. The fpp file will specify what goes into the auto-generated cpp and hpp files. Writing the fpp file will not implement component behavior on its own, but it will generate templates for most of what you will write in cpp and hpp files. 

In `Components/MathSender`, open `MathSender.fpp` and **entirely replace its contents with the following**: 


```fpp
# In: MathSender.fpp
module MathModule {

  @ Component for sending a math operation
  active component MathSender {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Port for sending the operation request
    output port mathOpOut: OpRequest

    @ Port for receiving the result
    async input port mathResultIn: MathResult

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Command receive port
    command recv port cmdIn

    @ Command registration port
    command reg port cmdRegOut

    @ Command response port
    command resp port cmdResponseOut

    @ Event port
    event port eventOut

    @ Telemetry port
    telemetry port tlmOut

    @ Text event port
    text event port textEventOut

    @ Time get port
    time get port timeGetOut

    # ----------------------------------------------------------------------
    # Commands
    # ----------------------------------------------------------------------

    @ Do a math operation
    async command DO_MATH(
                           val1: F32 @< The first operand
                           op: MathOp @< The operation
                           val2: F32 @< The second operand
                         )

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Math command received
    event COMMAND_RECV(
                        val1: F32 @< The first operand
                        op: MathOp @< The operation
                        val2: F32 @< The second operand
                      ) \
      severity activity low \
      format "Math command received: {f} {} {f}"

    @ Received math result
    event RESULT(
                  result: F32 @< The math result
                ) \
      severity activity high \
      format "Math result is {f}"

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ The first value
    telemetry VAL1: F32

    @ The operation
    telemetry OP: MathOp

    @ The second value
    telemetry VAL2: F32

    @ The result
    telemetry RESULT: F32

  }

}
```

## About this Component 
 
The above code defines `MathSender` component. The component is **active**, which means it has its own thread.

Inside the definition of the `MathSender` component are several specifiers. We have divided the specifiers into five groups.

1. **General ports:** These are user-defined ports for application-specific functions.
There are two general ports: an output port `mathOpOut` of type `OpRequest` and an input port `mathResultIn` of type `MathResult`.
Notice that these port specifiers use the ports that you defined.
The input port is **asynchronous**. This means that invoking the port (i.e., sending data on the port) puts a message on a queue. The handler runs later, on the thread of this component.

2. **Special ports:** These are ports that have a special meaning in F Prime.
They are ports for registering commands with the dispatcher, receiving commands, sending command responses, emitting event reports, emitting telemetry, and getting the time.

3. **Commands:** These are commands sent from the ground or from a sequencer and dispatched to this component.
There is one command `DO_MATH` for doing a math operation.
The command is asynchronous. This means that when the command arrives, it goes on a queue and its handler is later run on the thread of this component 

4. **Events:** These are event reports that this component can emit.
There are two event reports, one for receiving a command and one for receiving a result.

5. **Telemetry:** These are **channels** that define telemetry points that the this component can emit.
There are four telemetry channels: three for the arguments to the last command received and one for the last result received.

> For more information on defining components, see the [_FPP User's Guide_](https://fprime-community.github.io/fpp/fpp-users-guide.html#Defining-Components).


## Generate the Implementation Files

Now you have written the FPP code for the component, but the cpp and hpp files do not yet reflect the changes you have made to the fpp file. To get the cpp and hpp to reflect the specs you have defined in the fpp, you need to use the implement command as shown below:

```shell
# In: MathSender
fprime-util impl 
```

Now, In `MathSender`, you will see two new files, `MathSender.template.cpp` and `MathSender.template.hpp`. The template files are the files you just generated using the FPP model. Whenever F' generates code, it creates new file with the `.template.` so as to not burn down any old code. In this case, you did not write anything in the original `MathSender.cpp` or `MathSender.hpp`, so you can use a move command to replace the old code with the new code:


```shell 
# In: MathSender
mv MathSender.template.cpp MathSender.cpp
mv MathSender.template.hpp MathSender.hpp
```

Build MathSender to make sure everything worked as expected.

```shell 
# In: MathSender 
fprime-util build 
```

## Wait... Shouldn't You Add this to the Build? 

If you've been paying attention to the tutorial thus far, you might be getting some warning bells that you have not added your new component to the build. Fear not, when using `fprime-util new --component` all of the `CMakeLists.txt` and `project.cmake` work was done for you! Take a look at both files to verify for yourself. 

## Summary 

You are about two thirds of the way through finishing `MathSender`. In the next section you will implement `MathSender`'s component  behavior.


**Next:** [Creating Components Part 2: Implementing MathSender Behavior](./creating-components-2.md)